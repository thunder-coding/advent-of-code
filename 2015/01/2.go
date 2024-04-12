package main

import (
	"fmt"
	"io"
	"os"
)

func main() {
	input, err := os.Open("./2015/01/input.txt")
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error opening input file")
		os.Exit(1)
	}
	floor := 0
	basement := -1
	count := 0
	for true {
		count++
		b := make([]byte, 1)
		_, err := input.Read(b)
		if err != nil {
			if err == io.EOF {
				fmt.Fprintln(os.Stderr, "Santa never reached the basement")
				os.Exit(1)
			}
			fmt.Fprintln(os.Stderr, "Unexpected error when reading input file")
			os.Exit(1)
		}
		switch string(b) {
		case "(":
			floor++
		case ")":
			floor--
		default:
			fmt.Fprintln(os.Stderr, "Warning unexpected character '", string(b), "in input.txt")
		}
		if floor == basement {
			fmt.Println(count)
			break
		}
	}
}
