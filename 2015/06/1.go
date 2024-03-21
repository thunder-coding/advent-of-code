package main

import (
	"fmt"
	"os"

	"github.com/thunder-coding/advent-of-code/2015/06/input_parser"
)

type Lightgrid struct {
	lights [1000][1000]bool
}

func Lightgrid_turnon(lightgrid *Lightgrid, beg input_parser.Coordinate, end input_parser.Coordinate) {
	var stepx, stepy int
	if beg.X < end.X {
		stepx = +1
	} else {
		stepx = -1
	}
	if beg.Y < end.Y {
		stepy = +1
	} else {
		stepy = -1
	}
	for x := beg.X; x != (end.X + stepx); x += stepx {
		for y := beg.Y; y != (end.Y + stepy); y += stepy {
			lightgrid.lights[x][y] = true
		}
	}
}

func Lightgrid_turnoff(lightgrid *Lightgrid, beg input_parser.Coordinate, end input_parser.Coordinate) {
	var stepx, stepy int
	if beg.X < end.X {
		stepx = +1
	} else {
		stepx = -1
	}
	if beg.Y < end.Y {
		stepy = +1
	} else {
		stepy = -1
	}
	for x := beg.X; x != (end.X + stepx); x += stepx {
		for y := beg.Y; y != (end.Y + stepy); y += stepy {
			lightgrid.lights[x][y] = false
		}
	}
}
func Lightgrid_toggle(lightgrid *Lightgrid, beg input_parser.Coordinate, end input_parser.Coordinate) {
	var stepx, stepy int
	if beg.X < end.X {
		stepx = +1
	} else {
		stepx = -1
	}
	if beg.Y < end.Y {
		stepy = +1
	} else {
		stepy = -1
	}
	for x := beg.X; x != (end.X + stepx); x += stepx {
		for y := beg.Y; y != (end.Y + stepy); y += stepy {
			lightgrid.lights[x][y] = !lightgrid.lights[x][y]
		}
	}
}

func Lightgrid_counton(lightgrid *Lightgrid) uint32 {
	var count uint32
	for x := 0; x != 1000; x++ {
		for y := 0; y != 1000; y++ {
			if lightgrid.lights[x][y] {
				count += 1
			}
		}
	}
	return count
}

func main() {
	input, err := os.Open("./2015/06/input.txt")
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error opening input file")
		os.Exit(1)
	}
	stat, _ := input.Stat()
	size := stat.Size()
	data := make([]byte, size)
	input.Read(data)
	var cur int64 = 0
	var lightgrid Lightgrid
	for {
		instruction, err := input_parser.ParseInstruction(&data, size, &cur)
		if err != nil {
			if err == input_parser.EEof {
				break
			}
			fmt.Fprintf(os.Stderr, err.Error())
			os.Exit(1)
		}

		switch instruction.Action {
		case input_parser.TurnOn:
			Lightgrid_turnon(&lightgrid, instruction.Beg, instruction.End)
		case input_parser.TurnOff:
			Lightgrid_turnoff(&lightgrid, instruction.Beg, instruction.End)
		case input_parser.Toggle:
			Lightgrid_toggle(&lightgrid, instruction.Beg, instruction.End)
		}
	}
	fmt.Println(Lightgrid_counton(&lightgrid))
}
