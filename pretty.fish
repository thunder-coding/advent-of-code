#!/usr/bin/fish
function queue
  if not test (count (jobs)) -lt (nproc)
    wait
  end
  fish -c "$argv"
end

for file in 20*/*/*.{c,cpp,h,hpp}
  queue clang-format -i $file
end
for file in 20*/*/*.js
  queue prettier -w $file
end
for file in 20*/*/*.go
  queue go fmt $file
end
for file in 20*/*/*.py
  queue black $file
end
