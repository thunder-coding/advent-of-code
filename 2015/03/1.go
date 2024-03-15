package main

import (
	"fmt"
	"io"
	"os"
)

type Coordinate struct {
	x int
	y int
}

func main() {
	input, err := os.Open("./2015/03/input.txt")
	if err != nil {
		fmt.Fprintln(os.Stderr, "Unable to open input file")
		os.Exit(1)
	}
	var b = make([]byte, 1)
	santa := Coordinate{0, 0}
	houses := make(map[Coordinate]uint)
	houses[santa] = 1
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
		case "^":
			santa.y++
		case "v":
			santa.y--
		case "<":
			santa.x--
		case ">":
			santa.x++
		default:
			fmt.Fprintln(os.Stderr, "Unexpected character '", string(b), "'")
		}
		houses[santa]++
	}
	fmt.Println("Number of houses with atleast 1 gift is", len(houses))
}
