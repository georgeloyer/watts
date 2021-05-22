#!/bin/sh
#
# run-joymouse.sh
# wrapper script to fork joymouse daemon during startup
# see references to this script in joymouse.service
# the running version is a link to this file at /usr/local/bin

DISPLAY=:0
export DISPLAY

r=`ps -ef | grep joymouse | grep -v grep | grep -vc run-joymouse`
if [ "$r" -eq 0 ] ; then
  /usr/local/bin/joymouse 2>&1 &
  echo "joymouse daemon started"
else
  echo "joymouse daemon is already running"
fi
exit 0
