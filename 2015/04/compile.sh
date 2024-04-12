pre_test() {
  "$CC" "${CFLAGS[@]}" -lm "${problem}/md5_precompute.c" -o "out/${problem}/md5_precompute"
  "out/${problem}/md5_precompute"
}

c_compile() {
  "$CC" "${CFLAGS[@]}" -lm "${problem}/${part}.c" "${problem}/md5.c" -o "out/${problem}/${part}.c"
}

cpp_compile() {
  "$CXX" "${CXXFLAGS[@]}" -DOPENSSL_API_COMPAT=0x10100000L "${LDFLAGS[@]}" -lcrypto "${problem}/${part}.cpp" -o "out/${problem}/${part}.cpp"
}
