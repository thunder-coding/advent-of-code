package wire

import (
	"errors"

	"github.com/thunder-coding/advent-of-code/2015/07/parser"
)

type WireStatus uint8

const (
	NotCalculated WireStatus = iota
	Calculating
	Calculated
)

type WireInfo struct {
	Status     WireStatus
	Calculated uint16
	Gate       parser.Gate
	A, B       parser.Signal
}

type Wires map[string]*WireInfo

var (
	EWireNotInConnection = errors.New("Wire not found")
	ERecursion           = errors.New("Recursion detected")
)

func CalculateSignal(wireId string, wires *Wires) (uint16, error) {
	var value, a, b uint16
	var err error
	wireInfo, contains := (*wires)[wireId]
	if !contains {
		return value, EWireNotInConnection
	}
	switch wireInfo.Status {
	case Calculated:
		return wireInfo.Calculated, nil
	case Calculating:
		return value, ERecursion
	}
	wireInfo.Status = Calculating
	if wireInfo.A.Type == parser.SignalFromWire {
		a, err = CalculateSignal(wireInfo.A.Wire, wires)
		if err != nil {
			return value, err
		}
	} else /*if wireInfo.A.Type == parser.Raw */ {
		a = wireInfo.A.Raw
	}
	switch wireInfo.Gate {
	case parser.And, parser.Or, parser.LShift, parser.RShift:
		if wireInfo.B.Type == parser.SignalFromWire {
			b, err = CalculateSignal(wireInfo.B.Wire, wires)
			if err != nil {
				return value, err
			}
		} else /*if wireInfo.B.Type == parser.Raw */ {
			b = wireInfo.B.Raw
		}
	}
	switch wireInfo.Gate {
	case parser.Not:
		value = ^a
	case parser.And:
		value = a & b
	case parser.Or:
		value = a | b
	case parser.LShift:
		value = a << b
	case parser.RShift:
		value = a >> b
	case parser.Copy:
		value = a
	}
	wireInfo.Status = Calculated
	wireInfo.Calculated = value
	return value, nil
}
