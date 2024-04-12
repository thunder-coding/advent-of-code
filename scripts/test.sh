#!/usr/bin/bash
set -e

[ -v CC ] || CC="clang"
[ -v CXX ] || CXX="clang++"
[ -v CFLAGS ] || CFLAGS=("-Wall" "-Wextra" "-pedantic" "-Werror" "-Wno-newline-eof")
[ -v CXXFLAGS ] || CXXFLAGS=("-Wall" "-Wextra" "-pedantic" "-Werror" "-Wno-newline-eof" "-std=c++20" "-fno-exceptions" "-stdlib=libc++")
[ -v LDFLAGS ] || LDFLAGS=("-fuse-ld=lld")

orig_CFLAGS=("${CFLAGS[@]}")
orig_CXXFLAGS=("${CXXFLAGS[@]}")
orig_LDFLAGS=("${LDFLAGS[@]}")

max_procs=$(("$(nproc)" * 4))
fail_file="$(mktemp)"
queue() {
  if jobs | count "${max_procs}" 2>/dev/null; then
    wait -n || rm -f "${fail_file}"
  fi
  "$@" &
}
do_test() {
  if ! [ -a "${problem}/${part}.${lang}" ]; then
    echo "SKIPPING ${problem}/${part}.${lang} as solution is done implemented yet"
  fi
  if ! "${lang}"_compile; then
    echo "ERROR_COMPILE ${problem}/${part}.${lang}"
    return 1
  fi
  if [ "$("${lang}_exec")" != "$output" ]; then
    echo "FAIL ${problem}/${part}.${lang}"
    return 1
  fi
  echo "PASS ${problem}/${part}.${lang}"
}

test_problem() {
  if ! [ -d "${problem}" ]; then
    echo "ERROR: ${problem} is either not a directory or does not exist"
    rm -f "${fail_file}"
    return
  fi
  mkdir -p "out/${problem}"
  # if compile.sh overrides the variables, do restore the original values
  CFLAGS=("${orig_CFLAGS[@]}")
  CXXFLAGS=("${orig_CXXFLAGS[@]}")
  LDFLAGS=("${orig_LDFLAGS[@]}")
  pre_test() {
    :
  }
  bash_compile() {
    :
  }
  c_compile() {
    "$CC" "${CFLAGS[@]}" "${LDFLAGS[@]}" "${problem}/${part}.c" -o "out/${problem}/${part}.c"
  }
  cpp_compile() {
    "$CXX" "${CXXFLAGS[@]}" "${LDFLAGS[@]}" "${problem}/${part}.cpp" -o "out/${problem}/${part}.cpp"
  }
  go_compile() {
    go build -o "out/${problem}/${part}.go" "${problem}/${part}.go"
  }
  js_compile() {
    :
  }
  py_compile() {
    :
  }
  bash_exec() {
    bash "${problem}/${part}.bash"
  }
  c_exec() {
    "out/${problem}/${part}.c"
  }
  cpp_exec() {
    "out/${problem}/${part}.cpp"
  }
  go_exec() {
    "out/${problem}/${part}.go"
  }
  py_exec() {
    python "${problem}/${part}.py"
  }
  js_exec() {
    node "${problem}/${part}.js"
  }
  # Let individual problems override the compile step
  if [ -a "${problem}/compile.sh" ]; then
    . "${problem}/compile.sh"
  fi
  pre_test
  for part in {1..2}; do
    if ! [ -a "${problem}/${part}.output" ]; then
      echo "ERROR: missing output for ${problem}/${part}"
      rm -f "${fail_file}"
      continue
    fi
    output="$(cat "${problem}/${part}.output")"
    for lang in {bash,c,cpp,go,js,py}; do
      queue do_test
    done
  done
}
if [ $# = 0 ]; then
  for year in {2015..2023}; do
    for day in {01..25}; do
      problem="${year}/${day}"
      test_problem
    done
  done
else
  for problem in "$@"; do
    test_problem
  done
fi

wait || rm -f "${fail_file}"

if ! [ -a "${fail_file}" ]; then
  exit 1
fi

rm -f "${fail_file}"
