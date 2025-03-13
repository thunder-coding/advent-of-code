#!/usr/bin/bash
set -e
if [ "${#@}" != 2 ]; then
  echo "Usage $0 <year> <day>"
  exit 1
fi

year=$1
day=$2

if ! [ -f scripts/headers.txt ]; then
  echo "Please create a file scripts/headers.txt with the cookies from browser after logging in"
  exit 1
fi

if ! curl -H @scripts/headers.txt --compressed "https://adventofcode.com/${year}/day/$(printf "%d" ${day})/input" -o "src/year${year}/day$(printf "%02d" ${day})/input.txt" > /dev/null 2>&1; then
  echo "Failed to fetch input"
  exit 1
fi