pre_test() {
  re2c "${problem}/input_parser.c.re" -o "${problem}/input_parser.c"
  re2c "${problem}/input_parser.cpp.re" -o "${problem}/input_parser.cpp"
  re2go "${problem}/input_parser/parser.go.re" -o "${problem}/input_parser/parser.go"
}

c_compile() {
  "$CC" "${CFLAGS[@]}" "${problem}/${part}.c" "${problem}/input_parser.c" -o "out/${problem}/${part}.c"
}

cpp_compile() {
  "$CXX" "${CXXFLAGS[@]}" "${LDFLAGS[@]}" "${problem}/${part}.cpp" "${problem}/input_parser.cpp" -o "out/${problem}/${part}.cpp"
}
