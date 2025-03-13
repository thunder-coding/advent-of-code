#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>
#include <string>

#include "../utils/problems.h"

auto main() -> int {
  for (const auto& problem : gProblems) {
    try {
      std::ifstream inputFile(problem.second.inputFilePath);
      if (!inputFile) {
        throw std::runtime_error("Failed to open input file: " +
                                 problem.second.inputFilePath + "\n");
      }
      const std::string input(std::istreambuf_iterator<char>{inputFile}, {});
      std::ifstream answerFile(problem.second.answerFilePath);
      if (!answerFile) {
        throw std::runtime_error("Failed to open answer file : " +
                                 problem.second.answerFilePath + "\n");
      }
      const std::string answer(std::istreambuf_iterator<char>{answerFile}, {});
      const std::string receivedAnswer = problem.second.solution(input);
      if (answer != receivedAnswer) {
        throw std::runtime_error(
            "Solution to " + problem.first +
            " does not match the answer\nExpected answer: " + answer +
            "\nGot:             " + receivedAnswer);
      }
      std::cout << "PASS: " + problem.first + "\n";
    } catch (const std::exception& e) {
      std::cout << "FAIL: " + problem.first + "\n";
      std::cerr << e.what();
    }
  }
}