#!/usr/bin/bash
set -e
# This may take around hanf an hour to run even on moderm hardware
secret="$(cat ./2015/04/input.txt)"
answer=1
while true; do
  if [[ "$(echo -n "${secret}${answer}" | md5sum)" == "000000"* ]]; then
    echo $answer
    exit 0
  fi
  answer=$((answer + 1))
done
