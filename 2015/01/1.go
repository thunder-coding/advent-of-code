package main

import (
	"fmt"
	"io"
	"os"
)

func main() {
	input, err := os.Open("./2015/01/input.txt")
	if err != nil {
		fmt.Fprintln(os.Stderr, "Unable to open input file")
		os.Exit(1)
	}
	var b = make([]byte, 1)
	var floor = 0
	for true {
		_, err := input.Read(b)
		if err != nil {
			if err == io.EOF {
				break
			}
			fmt.Fprintln(os.Stderr, "Unexpected Error when reading input.txt", err)
			os.Exit(1)
		}
		switch string(b) {
		case "(":
			floor++
		case ")":
			floor--
		default:
			fmt.Fprintln(os.Stderr, "Unexpected character '", string(b), "'")
		}
	}

	fmt.Println("Santa will end up on floor ", floor)
}
