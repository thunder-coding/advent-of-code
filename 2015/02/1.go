package main

import (
	"fmt"
	"io"
	"os"
	"slices"
)

func main() {
	input, err := os.Open("./2015/02/input.txt")
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error opening input file")
		os.Exit(1)
	}
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error reading from input file")
		os.Exit(1)
	}
	var sides = make([]int, 3)
	var index = 0
	var area = 0
	for true {
		b := make([]byte, 1)
		_, err := input.Read(b)
		if err == io.EOF {
			break
		}
		char := int(b[0])
		switch {
		case char >= '0' && char <= '9':
			sides[index] *= 10
			sides[index] += (char - '0')
		case char == '\n':
			if index != 2 {
				fmt.Fprintln(os.Stderr, "A cuboid has exactly 3 sides, not", index+1)
				os.Exit(1)
			}
			slices.Sort(sides)
			index = 0
			area += (3*sides[0]*sides[1] + 2*sides[2]*(sides[0]+sides[1]))
			sides[0], sides[1], sides[2] = 0, 0, 0
		case char == 'x':
			index++
			if index == 3 {
				fmt.Fprintln(os.Stderr, "A cuboid has exactly 3 sides")
				os.Exit(1)
			}
		default:
			fmt.Fprintln(os.Stderr, "Unknown character in input file:", char)
			os.Exit(1)
		}
	}
	fmt.Println("Area of wrapping paper required is", area, "sq. feet")
}
