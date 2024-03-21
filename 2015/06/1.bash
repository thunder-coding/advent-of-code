#!/usr/bin/bash
set -e

lightgrid=()

for x in $(seq 0 999); do
  for y in $(seq 0 999); do
    index=$((1000 * x + y))
    lightgrid[index]=0
  done
done

lightgrid_turnon() {
  for x in $(seq "$1" "$3"); do
    for y in $(seq "$2" "$4"); do
      index=$((1000 * x + y))
      lightgrid[index]=1
    done
  done
}

lightgrid_turnoff() {
  for x in $(seq "$1" "$3"); do
    for y in $(seq "$2" "$4"); do
      index=$((1000 * x + y))
      lightgrid[index]=0
    done
  done
}

lightgrid_toggle() {
  for x in $(seq "$1" "$3"); do
    for y in $(seq "$2" "$4"); do
      index=$((1000 * x + y))
      if [ "${lightgrid[index]}" = 0 ]; then
        lightgrid[index]=1
      else
        lightgrid[index]=0
      fi
    done
  done
}

lightgrid_counton() {
  count=0
  for x in $(seq 0 999); do
    for y in $(seq 0 999); do
      index=$((1000 * x + y))
      count=$((count + lightgrid[index]))
    done
  done

  echo $count
}

while read -r line || [ -n "${line}" ]; do
  # Remove trailing newline
  line=${line%$'\n'}
  instruction=
  if [[ ${line} == "turn on "* ]]; then
    instruction="turn on"
  elif [[ ${line} == "turn off "* ]]; then
    instruction="turn off"
  elif [[ ${line} == "toggle "* ]]; then
    instruction="toggle"
  else
    echo "Error parsing instruction from input file on line: ${line}"
    exit 1
  fi
  line="${line#"${instruction} "}"

  beg_coordinate="${line%%" through "*}"
  beg_x="${beg_coordinate%%","*}"
  beg_y="${beg_coordinate##*","}"
  end_coordinate="${line##*" through "}"
  end_x="${end_coordinate%%","*}"
  end_y="${end_coordinate##*","}"

  begx=
  begy=
  endx=
  endy=
  if [ "$beg_x" -lt "$end_x" ]; then
    begx="$beg_x"
    endx="$end_x"
  else
    begx="$end_x"
    endx="$beg_x"
  fi
  if [ "$beg_y" -lt "$end_y" ]; then
    begy="$beg_y"
    endy="$end_y"
  else
    begy="$end_y"
    endy="$beg_y"
  fi

  case "${instruction}" in
  "turn on")
    lightgrid_turnon $begx $begy $endx $endy
    ;;
  "turn off")
    lightgrid_turnoff $begx $begy $endx $endy
    ;;
  "toggle")
    lightgrid_toggle $begx $begy $endx $endy
    ;;
  esac
done <./2015/06/input.txt

lightgrid_counton
