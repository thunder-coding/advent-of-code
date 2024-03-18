#!/usr/bin/bash
set -e
santa_x=0
santa_y=0
bot_x=0
bot_y=0
positions=()
positions+=("(0,0)")
while read -r line || [ -n "${line}" ]; do
  # Remove trailing newline
  line=${line%$'\n'}
  for i in $(seq 0 $((${#line} - 1))); do
    if [ "$((i % 2))" = 0 ]; then
      char=${line:i:1}
      if [ "${char}" = "^" ]; then
        santa_y=$((santa_y + 1))
      elif [ "${char}" = "v" ]; then
        santa_y=$((santa_y - 1))
      elif [ "${char}" = "<" ]; then
        santa_x=$((santa_x - 1))
      elif [ "${char}" = ">" ]; then
        santa_x=$((santa_x + 1))
      else
        echo "Unexpected character '${char}' found in input file"
        exit 1
      fi
      positions+=("(${santa_x},$santa_y)")
    else
      char=${line:i:1}
      if [ "${char}" = "^" ]; then
        bot_y=$((bot_y + 1))
      elif [ "${char}" = "v" ]; then
        bot_y=$((bot_y - 1))
      elif [ "${char}" = "<" ]; then
        bot_x=$((bot_x - 1))
      elif [ "${char}" = ">" ]; then
        bot_x=$((bot_x + 1))
      else
        echo "Unexpected character '${char}' found in input file"
        exit 1
      fi
      positions+=("(${bot_x},$bot_y)")
    fi
  done
done <./2015/03/input.txt

echo "${positions[@]}" | sed -e 's/ /\n/g' | sort -u | grep -c $'\n'
