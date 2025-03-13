#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "utils/problems.h"

auto main(int argc, char** argv) -> int {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <year>/<day>/<part>\n"
              << "       " << argv[0] << " <year>/<day>\n"
              << "       " << argv[0] << " <year>\n"
              << "Flags:\n"
              << "  -c: Check the answer against the answer file\n"
              << "  -w: Write the answer to the answer file (IGNORES -c)\n"
              << "Note that " << argv[0]
              << " does not contain any actual argument parsing and just "
                 "simply will apply -c and -w to the problems after the flags "
                 "have been supplied\n";
    return EXIT_FAILURE;
  }
  bool failure = false;
  bool check = false;
  bool write = false;
  for (int currentArgc = 1; currentArgc < argc; currentArgc++) {
    std::string problemName = argv[currentArgc];
    if (problemName == "-c") {
      check = true;
      continue;
    }
    if (problemName == "-w") {
      write = true;
      continue;
    }
    const auto lower_bound = gProblems.lower_bound(problemName);
    for (auto iterator = lower_bound; iterator != gProblems.end() &&
                                      iterator->first.starts_with(problemName);
         iterator++) {
      std::ifstream inputFile(iterator->second.inputFilePath);
      if (!inputFile) {
        std::cerr << "Failed to open input file: "
                  << iterator->second.inputFilePath << "\n";
        failure = true;
        continue;
      }
      const std::string input(std::istreambuf_iterator<char>{inputFile}, {});
      try {
        const auto receivedAnswer = iterator->second.solution(input);
        if (write) {
          std::ofstream answerFile(iterator->second.answerFilePath);
          if (!answerFile) {
            std::cerr << "Failed to open answer file: "
                      << iterator->second.answerFilePath << "\n";
            failure = true;
            continue;
          }
          answerFile << receivedAnswer;
          std::cout << "Successfully written the answer for " << iterator->first
                    << "\n";
        } else if (check) {
          std::ifstream answerFile(iterator->second.answerFilePath);
          if (!answerFile) {
            std::cerr << "Failed to open answer file: "
                      << iterator->second.answerFilePath << "\n";
            failure = true;
            continue;
          }
          const std::string answer(std::istreambuf_iterator<char>{answerFile},
                                   {});
          if (answer != receivedAnswer) {
            std::cerr << "Solution to " << iterator->first
                      << " does not match the answer\nExpected answer: "
                      << answer << "\nGot:             " << receivedAnswer
                      << "\n";
            failure = true;
            continue;
          }
          std::cout << "PASS: " << iterator->first << "\n";

        } else {
          std::cout << iterator->first << ": " << receivedAnswer << "\n";
        }
      } catch (const std::exception& e) {
        std::cerr << "Error while solving " << iterator->first << ": "
                  << e.what() << "\n";
        failure = true;
      }
    }
  }
  if (failure) {
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}