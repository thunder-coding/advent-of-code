#!/usr/bin/bash
set -e
length=0
while read -r line || [ -n "${line}" ]; do
  # Remove trailing newline
  line=${line%$'\n'}
  dimensions=()
  for i in $(seq 0 2); do
    dimensions+=(${line%%"x"*})
    line=${line:$((${#dimensions["${i}"]} + 1))}
  done
  dimensions=($(echo -n ${dimensions[0]}$'\n'${dimensions[1]}$'\n'${dimensions[2]} | sort -n))
  length=$((length + 2 * (dimensions[0] + dimensions[1]) + dimensions[0] * dimensions[1] * dimensions[2]))
done <./2015/02/input.txt

echo $length
