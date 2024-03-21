package input_parser

import "errors"

type Action int8

const (
	TurnOn Action = iota
	TurnOff
	Toggle
)

var (
	EUnknownInstruction  = errors.New("unknown instruction")
	EInvalidSyntax       = errors.New("invalid syntax")
	EEof                 = errors.New("end of file")
	EUnexpectedCharacter = errors.New("unexpected character")
	EUnexpectedEof       = errors.New("Unexpected end of file")
)

type Coordinate struct {
	X int
	Y int
}

type Instruction struct {
	Action   Action
	Beg, End Coordinate
}
