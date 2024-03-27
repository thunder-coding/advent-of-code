#!/usr/bin/fish
rm tasks.sh
for file in 20*/**/*.{{c,cpp}{,.re},h,hpp}
  echo clang-format -i "$file" >> tasks.sh
end
for file in 20*/**/*.js
  echo prettier -w "$file" >> tasks.sh
end
for file in 20*/**/*.go{,.re}
  echo gofmt -w "$file" >> tasks.sh
end
for file in 20*/**/*.py
  echo black "$file" >> tasks.sh
end
for file in 20*/**/*.bash
  echo shfmt -s -w "$file" >> tasks.sh
end

parallel < tasks.sh
