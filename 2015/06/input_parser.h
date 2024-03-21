#ifndef ADVENT_OF_CODE_2015_06_INPUT_PARSER_H
#define ADVENT_OF_CODE_2015_06_INPUT_PARSER_H

#include <stdio.h>
enum Action { TurnOn, TurnOff, Toggle, Eof, Error };

struct Instruction {
  enum Action action;
  int startx, starty, endx, endy;
};

void Parse_instruction(FILE *file, struct Instruction *instruction);

#endif
