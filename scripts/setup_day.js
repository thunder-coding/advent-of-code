#!/usr/bin/node
"use strict";
const fs = require("fs");
const path = require("path");

if (process.argv.length !== 4) {
  console.error(`Usage: ${process.argv[0]} <year> <day>`);
  process.exit(1);
}

let year = Number(process.argv[2]);
if (!Number.isInteger(year)) {
  console.error("Year must be an integer");
  process.exit(1);
}
let day = Number(process.argv[3]);
if (!Number.isInteger(day)) {
  console.error("Day must be an integer");
  process.exit(1);
}
let dayStr = day.toString();

if (day < 10) {
  dayStr = `0${day}`;
}

let day_folder = `src/year${year}/day${dayStr}`;

fs.mkdirSync(day_folder, { recursive: true });

fs.writeFileSync(
  `${day_folder}/mod.rs`,
  `pub mod parse;
pub mod part1;
pub mod part2;`,
);

fs.writeFileSync(
  `${day_folder}/parse.rs`,
  ``
)

fs.writeFileSync(
  `${day_folder}/parse.cc`,
  ''
)

fs.writeFileSync(
  `${day_folder}/parse.h`,
  `#ifndef ADVENT_OF_CODE_YEAR${year}_DAY${dayStr}_PARSE_H
#define ADVENT_OF_CODE_YEAR${year}_DAY${dayStr}_PARSE_H

namespace Year${year}::Day${dayStr} {

}

#endif
)`)

for (let part of [1, 2]) {
  fs.writeFileSync(
    `${day_folder}/part${part}.cc`,
    `#include <string>

#include "../solutions.h"

auto Year${year}::Day${dayStr}::Part${part}(const std::string& input) -> std::string {
  return Ok(input);
}`,
  );

  fs.writeFileSync(
    `${day_folder}/part${part}.rs`,
    `pub fn part${part}(input: String) -> Result<String, String> {
  return input;
}`,
  );
}

fs.appendFileSync(`src/year${year}/mod.rs`, `pub mod day${dayStr};\n`);
if (!fs.readFileSync(`src/lib.rs`).toString().match(`mod year${year};`)) {
  fs.appendFileSync(`src/lib.rs`, `pub mod year${year}\n;`);
}

if (!fs.existsSync(`src/year${year}/solutions.h`)) {
  fs.writeFileSync(
    `src/year${year}/solutions.h`,
    `#ifndef ADVENT_OF_CODE_YEAR${year}_SOLUTIONS_H
#define ADVENT_OF_CODE_YEAR${year}_SOLUTIONS_H
#include "../utils/solutions.h"

SOLUTION_FOR_YEAR(${year})
#endif
`,
  );
}

fs.writeFileSync(
  `src/utils/problems.rs`,
  fs
    .readFileSync(`src/utils/problems.rs`)
    .toString()
    .replace(
      `  return problems_list;`,
      `  add_problems_for_day!(problems_list, ${year}, ${day});\n  return problems_list;`,
    ),
);

fs.writeFileSync(
  `src/utils/problems.h`,
  fs
    .readFileSync(`src/utils/problems.h`)
    .toString()
    .replace(
      `};\n// clang-format on`,
      `  SOLUTION_INITIALISERLIST_FOR_DAY(${year}, ${dayStr})\n};\n// clang-format on`,
    ),
);

if (
  !fs
    .readFileSync(`src/utils/problems.h`)
    .toString()
    .match(`#include "../year${year}/solutions.h"`)
) {
  fs.writeFileSync(
    `src/utils/problems.h`,
    fs
      .readFileSync(`src/utils/problems.h`)
      .toString()
      .replace(
        `#include "solutions.h"`,
        `#include "../year${year}/solutions.h"\n#include "solutions.h"`,
      ),
  );
}

if (!fs.readFileSync(`src/main.rs`).toString().match(`mod year${year};`)) {
  fs.writeFileSync(
    `src/main.rs`,
    fs
      .readFileSync(`src/main.rs`)
      .toString()
      .replace(`\n\nfn main()`, `\nmod year${year};\n\nfn main()`),
  );
}

fs.writeFileSync(
  `CMakeLists.txt`,
  fs
    .readFileSync(`CMakeLists.txt`)
    .toString()
    .replace(
      `)\n\nadd_executable(AOC\n`,
      `  src/year${year}/day${dayStr}/part1.cc
src/year${year}/day${dayStr}/part2.cc
src/year${year}/day${dayStr}/parse.cc
)

add_executable(AOC
`,
    ),
);

let headers = {};
fs.readFileSync(`scripts/headers.txt`)
  .toString()
  .split("\n")
  .map((line) => line.split(": "))
  .forEach(([key, value]) => {
    headers[key] = value;
  });

fetch(`https://adventofcode.com/${year}/day/${day}/input`, {
  headers,
})
  .then((response) => response.text())
  .then((data) => {
    fs.writeFileSync(`src/year${year}/day${dayStr}/input.txt`, data);
  });