set -e
cat ./2015/05/input.txt | grep -E '([aeiouAEIOU]).*?([aeiouAEIOU]).*?([aeiouAEIOU]).*?' | grep -E '(.)\1' | grep -E -v 'ab|cd|pq|xy' -c
