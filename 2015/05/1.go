package main

import (
	"fmt"
	"os"
	"regexp"
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
		vowelsCount := 0
		// We can't use "(.){2}" a regeex as Go's regex is broken
		atleastOneLetterThatAppearTwiceInARow := false
		cold := "this is a joke string"
		for _, c := range strings.Split(line, "") {
			if c == cold {
				atleastOneLetterThatAppearTwiceInARow = true
			}
			switch c {
			case "a", "A", "e", "E", "i", "I", "o", "O", "u", "U":
				vowelsCount++
			}
			cold = c
		}
		hasAtleastThreeVowels := vowelsCount >= 3
		hasForbiddenStrings := regexp.MustCompile("ab|cd|pq|xy").MatchString(line)
		if hasAtleastThreeVowels && atleastOneLetterThatAppearTwiceInARow && !hasForbiddenStrings {
			niceCount++
		}
	}
	fmt.Println(niceCount)
}
