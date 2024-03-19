package main

import (
	"fmt"
	"os"
	"strings"
)

func main() {
	input, err := os.Open("./2015/05/input.txt")
	if err != nil {
		fmt.Fprintln(os.Stderr, "Unable to open input file")
		os.Exit(1)
	}
	stat, _ := input.Stat()
	b := make([]byte, stat.Size())
	input.Read(b)
	niceCount := 0
	for _, line := range strings.Split(string(b), "\n") {
		pairs := make(map[string]int)
		oldpair := ""
		condition1, condition2 := false, false
		for i := 0; i+1 < len(line); i++ {
			pair := line[i : i+2]
			value, contains := pairs[pair]
			if !condition1 && contains && value+2 <= i {
				condition1 = true
			}
			if !condition2 && len(oldpair) != 0 && oldpair[0] == pair[1] {
				condition2 = true
			}
			if condition1 && condition2 {
				fmt.Println(line)
				niceCount++
				break
			}
			oldpair = pair
			if !contains {
				pairs[pair] = i
			}
		}
	}
	fmt.Println(niceCount)
}
