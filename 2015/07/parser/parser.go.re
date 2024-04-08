package parser

import (
	"math"
)

func ParseInstruction(data *[]byte, size int64, cur *int64) (Instruction, error) {
	var instruction Instruction
	if *cur >= size {
		return instruction, EEof
	}
	gate, err := parseGate(data, size, cur)
	if err == ENotAGate {
		a, err := parseSignal(data, size, cur)
		if err != nil {
			return instruction, err
		}
		instruction.A = a

		if err := eatWhiteSpace(data, size, cur); err != nil {
			return instruction, err
		}

		gate, err := parseGate(data, size, cur)
		if err == nil {
			if gate != And && gate != Or && gate != LShift && gate != RShift {
				return instruction, EExpectedBinaryGate
			}
			instruction.Gate = gate
		} else if err == ENotAGate {
			// If not a gate, it should be a copy operation
			instruction.Gate = Copy
			goto before_arrow
		} else {
			return instruction, err
		}

		if err := eatWhiteSpace(data, size, cur); err != nil {
			return instruction, err
		}

		b, err := parseSignal(data, size, cur)
		if err != nil {
			return instruction, err
		}
		instruction.B = b

		if err := eatWhiteSpace(data, size, cur); err != nil {
			return instruction, err
		}
	} else if err == nil {
		// if the first token is a gate, it's supposed to be a NOT gate
		if gate == Not {
			instruction.Gate = Not
			if err := eatWhiteSpace(data, size, cur); err != nil {
				return instruction, err
			}
			a, err := parseSignal(data, size, cur)
			if err != nil {
				return instruction, err
			}
			instruction.A = a
			if err := eatWhiteSpace(data, size, cur); err != nil {
				return instruction, err
			}
		} else {
			return instruction, EUnexpectedGate
		}
	} else {
		return instruction, err
	}
before_arrow:
	/*!re2c
	  re2c:define:YYCTYPE = byte;
	  re2c:define:YYPEEK = "(*data)[*cur]";
	  re2c:define:YYSKIP = "*cur += 1";
	  re2c:define:YYBACKUP = "mar = *cur";
	  re2c:define:YYRESTORE = "*cur = mar";
	  re2c:define:YYLESSTHAN = "*cur >= size";
	  re2c:yyfill:enable = 0;
	  re2c:eof = 0;

	  "->" {
	    goto after_arrow
	  }
	  * {
	    return instruction, EExpectedArrow
	  }
	  $ {
	    return instruction, EUnexpectedEof
	  }
	*/
after_arrow:
	if err := eatWhiteSpace(data, size, cur); err != nil {
		return instruction, err
	}
	c, err := parseSignal(data, size, cur)
	if err != nil {
		return instruction, err
	}
	instruction.C = c
	if *cur != size && (*data)[*cur] != '\n' {
		return instruction, EExpectedNewline
	}
	*cur += 1
	return instruction, nil
}

func eatWhiteSpace(data *[]byte, size int64, cur *int64) error {
	if *cur >= size {
		return EUnexpectedEof
	}
	if (*data)[*cur] != ' ' {
		return EExpectedWhiteSpace
	}
	*cur += 1
	return nil
}

func parseGate(data *[]byte, size int64, cur *int64) (Gate, error) {
	if *cur >= size {
		return And, EUnexpectedEof
	}
	mar := *cur
	/*!re2c
		  re2c:define:YYCTYPE = byte;
		  re2c:define:YYPEEK = "(*data)[*cur]";
		  re2c:define:YYSKIP = "*cur += 1";
		  re2c:define:YYLESSTHAN = "*cur >= size";
		  re2c:yyfill:enable = 0;
		  re2c:eof = 0;

		  "AND" {
		    return And, nil
		  }
		  "OR" {
		    return Or, nil
		  }
		  "NOT" {
		    return Not, nil
		  }
		  "LSHIFT" {
		    return LShift, nil
		  }
		  "RSHIFT" {
		    return RShift, nil
		  }
	    * {
	      *cur = mar
	      return And, ENotAGate
	    }
		  $ {
		    return And, EUnexpectedEof
		  }
	*/
}

func parseSignal(data *[]byte, size int64, cur *int64) (Signal, error) {
	var signal Signal
	var str string
	beg := *cur
	if *cur >= size {
		return signal, EUnexpectedEof
	}
	/*!re2c
		  re2c:define:YYCTYPE = byte;
		  re2c:define:YYPEEK = "(*data)[*cur]";
		  re2c:define:YYSKIP = "str += string((*data)[*cur]); *cur += 1";
		  re2c:define:YYBACKUP = "mar = *cur";
		  re2c:define:YYRESTORE = "*cur = mar";
		  re2c:define:YYLESSTHAN = "*cur >= size";
		  re2c:yyfill:enable = 0;
		  re2c:eof = 0;

		  [a-z]+ {
		    signal.Type = SignalFromWire
		    signal.Wire = str
		    return signal, nil
		  }
		  [0-9]+ {
		    signal.Type = Raw
		    var value uint32
		    for i := 0; i != len(str); i += 1 {
		      value *= 10
		      value += uint32(str[i] - '0')
		      if value > math.MaxUint16 {
		        return signal, ENumberOutOfUint16Range
		      }
		    }
		    signal.Raw = uint16(value)
		    return signal, nil
		  }
	    * {
	      *cur = beg
	      return signal, ENotASignal
	    }
		  $ {
		    return signal, EUnexpectedEof
		  }
	*/
}
