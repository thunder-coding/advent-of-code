#!/usr/bin/fish
clang-format -i 20*/*/*.{c,cpp}
prettier -w 20*/*/*.js
go fmt 20*/*/*.go
black 20*/*/*.py
