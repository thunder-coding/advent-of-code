package parser

import "errors"

type Gate uint8

const (
	And Gate = iota
	Or
	LShift
	RShift
	Not
	Copy
)

var (
	EEof                    = errors.New("End of file")
	EUnexpectedEof          = errors.New("Unexpected end of file")
	ENotASignal             = errors.New("Expected signal found something else")
	EUnexpectedGate         = errors.New("unexpected gate found while parsing")
	ENotAGate               = errors.New("Expected gate found something else")
	EExpectedBinaryGate     = errors.New("Expected one of AND, OR, LSHIFT, RSHIFT found something else")
	EExpectedWireConnection = errors.New("Expected wire connection found raw signal")
	EExpectedArrow          = errors.New("Expected a arrow sign found something else")
	ENumberOutOfUint16Range = errors.New("The number in the signal is outside the range of uint16")
	EExpectedWhiteSpace     = errors.New("Expected to find whitespace character found something else")
	EExpectedNewline        = errors.New("Expected end of line found something else")
)

type SignalType uint8

const (
	Raw SignalType = iota
	SignalFromWire
)

type Signal struct {
	Type SignalType
	// AFAIK go doesn't have a really clean way to do type unions so let's just store both
	Raw  uint16
	Wire string
}

type Instruction struct {
	Gate    Gate
	A, B, C Signal
}
