set -e
cat ./2015/05/input.txt | grep -E '(.{2}).*\1' | grep -E '(.).\1' -c
