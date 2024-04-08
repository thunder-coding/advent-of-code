package main

import (
	"fmt"
	"os"

	"github.com/thunder-coding/advent-of-code/2015/07/parser"
	"github.com/thunder-coding/advent-of-code/2015/07/wire"
)

func main() {
	input, err := os.Open("./2015/07/input.txt")
	if err != nil {
		fmt.Fprintln(os.Stderr, "Error opening input file")
		os.Exit(1)
	}
	stat, _ := input.Stat()
	size := stat.Size()
	data := make([]byte, size+1)
	input.Read(data)
	var cur int64 = 0
	wires := make(wire.Wires)
	for i := 1; true; i += 1 {
		instruction, err := parser.ParseInstruction(&data, size, &cur)
		wireInfo := new(wire.WireInfo)
		_, contains := wires[instruction.C.Wire]
		if contains {
			fmt.Fprintln(os.Stderr, "A wire can only receive signal from one source, wire '", instruction.C.Wire, "' is receiving signal from multiple sources")
			os.Exit(1)
		}
		wires[instruction.C.Wire] = wireInfo
		wireInfo.Gate = instruction.Gate
		wireInfo.A = instruction.A
		wireInfo.B = instruction.B
		wireInfo.Status = wire.NotCalculated
		if err != nil {
			if err == parser.EEof {
				break
			}
			fmt.Fprintln(os.Stderr, err.Error(), i)
			os.Exit(1)
		}
	}
	val, err := wire.CalculateSignal("a", &wires)
	if err != nil {
		fmt.Fprintln(os.Stderr, err.Error())
		os.Exit(1)
	}

	for _, wireInfo := range wires {
		wireInfo.Status = wire.NotCalculated
	}

	bWireInf, contains := wires["b"]
	if !contains {
		fmt.Fprintln(os.Stderr, "Wire b not found in the circuit")
	}
	bWireInf.Status = wire.Calculated
	bWireInf.Calculated = val

	finalVal, err := wire.CalculateSignal("a", &wires)
	if err != nil {
		fmt.Fprintln(os.Stderr, err.Error())
		os.Exit(1)
	}
	fmt.Println(finalVal)
}
