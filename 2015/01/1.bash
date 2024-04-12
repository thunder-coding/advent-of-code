#!/usr/bin/bash
set -e
read -r INPUT <./2015/01/input.txt || [ -n "${INPUT}" ]
floor=0
for index in $(seq 0 $((${#INPUT} - 1))); do
  char=${INPUT:index:1}
  if [ "$char" = "(" ]; then
    floor=$((floor + 1))
  elif [ "$char" = ")" ]; then
    floor=$((floor - 1))
  fi
done

echo "${floor}"
