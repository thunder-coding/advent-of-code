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
	bot := Coordinate{0, 0}
	lastGiftBySanta := false
	var pos *Coordinate
	houses := make(map[Coordinate]uint)
	houses[santa] = 1
	for true {
		if lastGiftBySanta {
			pos = &bot
		} else {
			pos = &santa
		}
		lastGiftBySanta = !lastGiftBySanta
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
			pos.y++
		case "v":
			pos.y--
		case "<":
			pos.x--
		case ">":
			pos.x++
		default:
			fmt.Fprintln(os.Stderr, "Unexpected character '", string(b), "'")
		}
		houses[*pos]++
	}
	fmt.Println(len(houses))
}
