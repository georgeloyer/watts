/* Copyright 2018 The TensorFlow Authors. All Rights Reserved.

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

#ifndef TENSORFLOW_CORE_PLATFORM_ERROR_H_
#define TENSORFLOW_CORE_PLATFORM_ERROR_H_

#include <string>

#include "tensorflow/core/platform/platform.h"
#include "tensorflow/core/platform/status.h"

namespace tensorflow {

Status IOError(const string& context, int err_number);

}  // namespace tensorflow

#if defined(PLATFORM_WINDOWS)

#include <Windows.h>
// Windows.h #defines ERROR, but it is also used in
// tensorflow/core/util/event.proto
#undef ERROR

namespace tensorflow {
namespace internal {

std::string GetWindowsErrorMessage(DWORD err);
}
}  // namespace tensorflow

#endif

#endif  // TENSORFLOW_CORE_PLATFORM_ERROR_H_