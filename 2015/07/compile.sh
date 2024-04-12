pre_test() {
  re2c "${problem}/parseInstruction.c.re" -o "${problem}/parseInstruction.c"
  re2c "${problem}/parseInstruction.cpp.re" -o "${problem}/parseInstruction.cpp"
  re2go "${problem}/parser/parser.go.re" -o "${problem}/parser/parser.go"
}

c_compile() {
  "$CC" "${CFLAGS[@]}" "${problem}/${part}.c" "${problem}/WireMesh.c" "${problem}/parseInstruction.c" -o "out/${problem}/${part}.c"
}

cpp_compile() {
  "$CXX" "${CXXFLAGS[@]}" "${LDFLAGS[@]}" "${problem}/${part}.cpp" "${problem}/wire.cpp" "${problem}/parseInstruction.cpp" -o "out/${problem}/${part}.cpp"
}
