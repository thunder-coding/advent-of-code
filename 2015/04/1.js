"use strict";
const fs = require("node:fs");
const crypto = require("node:crypto");
let contents = fs.readFileSync("./2015/04/input.txt", "utf8").toString();

for (let i = 0; i < Number.MAX_SAFE_INTEGER; i++) {
  let hash = crypto
    .createHash("md5")
    .update(contents + i)
    .digest("hex");
  if (hash.startsWith("00000")) {
    console.log(i);
    process.exit(0);
  }
}

console.error("No integer till Number.MAX_SAFE_INTEGER mines the adventcoin");
process.exit(1);
