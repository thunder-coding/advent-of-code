#!/usr/bin/fish
function queue
  if not test (count (jobs)) -lt (nproc)
    wait
  end
  fish -c "$argv" &
end

for file in 20*/**/*.{{c,cpp}{,.re},h,hpp}
  queue clang-format -i $file
end
for file in 20*/**/*.js
  queue prettier -w $file
end
for file in 20*/**/*.go{,.re}
  queue gofmt -w $file
end
for file in 20*/**/*.py
  queue black $file
end
for file in 20*/**/*.bash
  queue shfmt -s -w $file
end
