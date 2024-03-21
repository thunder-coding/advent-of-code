package input_parser

func ParseInstruction(data *[]byte, size int64, cur *int64) (Instruction, error) {
	var instruction Instruction
	var mar int64
  if *cur >= size {
    return instruction, EEof
  }
	/*!re2c
	  re2c:define:YYCTYPE = byte;
	  re2c:define:YYPEEK = "(*data)[*cur]";
	  re2c:define:YYSKIP = "*cur += 1";
	  re2c:define:YYBACKUP = "mar = *cur";
	  re2c:define:YYRESTORE = "*cur = mar";
	  re2c:define:YYLESSTHAN = "*cur >= size";
	  re2c:yyfill:enable = 0;
	  re2c:eof = 0;

	  * {
	    return instruction, EUnknownInstruction
	  }
	  $ {
	    return instruction, EEof
	  }
	  "toggle" {
	    instruction.Action = Toggle
	    goto after_instruction
	  }
	  "turn on" {
	    instruction.Action = TurnOn
	    goto after_instruction
	  }
	  "turn off" {
	    instruction.Action = TurnOff
	    goto after_instruction
	  }
	*/
after_instruction:
	// Eat the whitespace
	if *cur == size {
		return instruction, EUnexpectedEof
	}
	if (*data)[*cur] != ' ' {
		return instruction, EInvalidSyntax
	}
	*cur += 1
  var err error
  instruction.Beg, err = parseCoordinate(data, size, cur)
  if err != nil {
    return instruction, err
  }
  // Eat the whitespace
	if *cur == size {
		return instruction, EUnexpectedEof
	}
	if (*data)[*cur] != ' ' {
		return instruction, EInvalidSyntax
	}
	*cur += 1

	/*!re2c
	  re2c:define:YYCTYPE = byte;
	  re2c:define:YYPEEK = "(*data)[*cur]";
	  re2c:define:YYSKIP = "*cur += 1";
	  re2c:define:YYBACKUP = "mar = *cur";
	  re2c:define:YYRESTORE = "*cur = mar";
	  re2c:define:YYLESSTHAN = "*cur >= size";
	  re2c:yyfill:enable = 0;
	  re2c:eof = 0;

	  * {
	    return instruction, EInvalidSyntax
	  }
	  $ {
	    return instruction, EUnexpectedEof
	  }
	  "through" { goto before_end; }
	*/
before_end:
  // Eat the whitespace
	if *cur == size {
		return instruction, EUnexpectedEof
	}
	if (*data)[*cur] != ' ' {
		return instruction, EInvalidSyntax
	}
	*cur += 1
  instruction.End, err = parseCoordinate(data, size, cur)
  if err != nil {
    return instruction, err
  }
  // Eat the newline
  if *cur != size && (*data)[*cur] != '\n' {
    return instruction, EUnexpectedCharacter
  }
  *cur += 1
	return instruction, nil
}

func parseCoordinate(data *[]byte, size int64, cur *int64) (Coordinate, error) {
	var coordinate Coordinate
	num := &coordinate.X
	for {
		if *cur == size {
			if num == &coordinate.Y {
				return coordinate, nil
			} else {
				return coordinate, EUnexpectedEof
			}
		}
		ch := (*data)[*cur]
		switch ch {
		case '0', '1', '2', '3', '4', '5', '6', '7', '8', '9':
			*num *= 10
			*num += int(ch - '0')
		case ',':
			if num == &coordinate.X {
				num = &coordinate.Y
			} else {
				return coordinate, EUnexpectedCharacter
			}
		case ' ', '\n':
			if num == &coordinate.Y {
				return coordinate, nil
			} else {
				return coordinate, EUnexpectedCharacter
			}
		default:
			return coordinate, EUnexpectedCharacter
		}
		*cur += 1
	}
}
