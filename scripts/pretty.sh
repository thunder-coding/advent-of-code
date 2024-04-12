#!/usr/bin/bash
set -e
queue() {

  if jobs | count "$(nproc)" 2>/dev/null; then
    wait -n
  fi
  "$@" &
}

find . \
  -name '*.c' \
  -o -name '*.h' \
  -o -name '*.cpp' \
  -o -name '*.hpp' \
  -o -name '*.c.re' \
  -o -name '*.cpp.re' | grep -v '^./out' | while read -r file; do
  queue clang-format -i "$file"
done

find . \
  -name '*.js' | grep -v '^./out' | while read -r file; do
  queue prettier -w "$file"
done

find . \
  -name '*.go' \
  -o -name '*.go.re' | grep -v '^./out' | while read -r file; do
  queue gofmt -w "$file"
done

queue false
find . \
  -name '*.py' | grep -v '^./out' | while read -r file; do
  queue black "$file"
done

find . \
  -name '*.bash' \
  -o -name '*.sh' | grep -v '^./out' | while read -r file; do
  queue shfmt -s -w "$file"
done

wait
