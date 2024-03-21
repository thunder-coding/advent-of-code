#ifndef ADVENT_OF_CODE_2015_06_INPUT_PARSER_HPP
#define ADVENT_OF_CODE_2015_06_INPUT_PARSER_HPP

#include <fstream>
enum class Action { TurnOn, TurnOff, Toggle, Eof, Error };

struct Instruction {
  Action action;
  int startx, starty, endx, endy;
};

void Parse_instruction(std::ifstream &file, Instruction &instruction);

#endif
