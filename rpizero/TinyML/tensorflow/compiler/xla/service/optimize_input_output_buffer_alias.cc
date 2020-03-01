/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include "tensorflow/compiler/xla/service/optimize_input_output_buffer_alias.h"

#include <queue>
#include <string>
#include <vector>

#include "absl/container/flat_hash_map.h"
#include "absl/memory/memory.h"
#include "absl/strings/str_format.h"
#include "tensorflow/compiler/xla/shape_util.h"
#include "tensorflow/compiler/xla/status_macros.h"
#include "tensorflow/compiler/xla/util.h"
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/platform/types.h"

namespace xla {
namespace {

// Returns true if the given shape is a non-nested tuple.
bool IsNonNestedTuple(const Shape& shape) {
  return shape.IsTuple() && !ShapeUtil::IsNestedTuple(shape);
}

}  // namespace

StatusOr<bool> OptimizeInputOutputBufferAlias::Build(
    absl::Span<const Shape* const> input_shapes, const Shape& output_shape,
    HloInputOutputAliasConfig* alias_config) {
  bool changed = false;
  for (const Shape* input_shape : input_shapes) {
    TF_RET_CHECK(LayoutUtil::HasLayout(*input_shape));
    VLOG(1) << "input_shape:" << input_shape->ToString();
  }
  TF_RET_CHECK(LayoutUtil::HasLayout(output_shape));
  VLOG(1) << "output_shape:" << output_shape.ToString();

  // Tracks all buffers defined by the parameter in a flatten list.
  struct Entry {
    int param_number;
    Shape shape;
    ShapeIndex index;
    bool used;
  };
  std::vector<Entry> parameter_entries;
  for (int i = 0; i < input_shapes.size(); ++i) {
    ShapeUtil::ForEachSubshape(
        *input_shapes[i], [&](const Shape& subshape, const ShapeIndex& index) {
          if (subshape.IsTuple()) {
            return;
          }
          parameter_entries.emplace_back(Entry{i, subshape, index, false});
        });
  }

  // For each result buffer shape index, take the first unused parameter
  // buffer that matches the shape.
  TF_RETURN_IF_ERROR(ShapeUtil::ForEachSubshapeWithStatus(
      output_shape, [&](const Shape& subshape, const ShapeIndex& index) {
        if (subshape.IsTuple()) {
          return Status::OK();
        }
        for (Entry& entry : parameter_entries) {
          if (Shape::Equal()(entry.shape, subshape) && !entry.used) {
            changed = true;
            const ShapeIndex& input_index = entry.index;
            const ShapeIndex& output_index = index;
            if (!alias_config->ParameterHasAlias(0, input_index) &&
                !alias_config->OutputHasAlias(output_index)) {
              TF_RETURN_IF_ERROR(alias_config->SetUpAlias(
                  output_index, entry.param_number, input_index,
                  HloInputOutputAliasConfig::AliasKind::kSystemAlias));
            }
            entry.used = true;
            break;
          }
        }
        return Status::OK();
      }));
  return changed;
}

StatusOr<bool> OptimizeInputOutputBufferAlias::Run(HloModule* module) {
  HloInputOutputAliasConfig* alias_config =
      &module->input_output_alias_config();

  std::vector<const Shape*> input_shapes;
  input_shapes.reserve(module->entry_computation()->num_parameters());
  for (HloInstruction* i :
       module->entry_computation()->parameter_instructions()) {
    input_shapes.push_back(&i->shape());
  }
  return Build(input_shapes,
               module->entry_computation()->root_instruction()->shape(),
               alias_config);
}

}  // namespace xla