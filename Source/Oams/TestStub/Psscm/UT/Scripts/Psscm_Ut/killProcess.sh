#!/bin/bash

if [ -z $1 ]
   then
   echo "Usage: ./killProcess.sh <Process Name>"
else
   kill -9 `ps -eaf | grep $1 | cut -d ' ' -f 2` > /dev/null
fi
