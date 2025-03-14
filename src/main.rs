#![feature(btree_cursors)]
use std::io::Write;
use std::process::exit;
use std::{env::args, fs::File, io::Read};

mod utils;
use libc::{EXIT_FAILURE, EXIT_SUCCESS};
use utils::get_problems::get_problems;

mod year2015;

fn main() {
  let args: Vec<String> = args().collect();
  if args.len() < 2 {
    println!("Usage: {} <year>/<day>/<part>", args[0]);
    println!("       {} <year>/<day>", args[0]);
    println!("       {} <year>", args[0]);
    println!("Flags:");
    println!("  -c: Check the answer against the answer file");
    println!("  -w: Write the answer to the answer file (IGNORES -c)");
    println!(
      "Note that {} does not contain any actual argument parsing and just simply will apply -c and -w to the problems after the flags have been supplied",
      args[0]
    );
  }
  let mut failure = false;
  let mut check = false;
  let mut write = false;
  let problems = get_problems();
  for arg in args[1..].iter() {
    if arg == "-c" {
      check = true;
      continue;
    }
    if arg == "-w" {
      write = true;
      continue;
    }
    // Gotta love the Rust fanboys who wanna replace everything with Rust, but not look at how
    // terrible Rust actually is. I mean it doesn't even have lower_bound and upper_bound, I mean it
    // does but only in nightly. mEm0rY sAfE
    // Honestly I do like the idea of a memory safe language, but I don't like being as stubborn as
    // Rust on that. I like being on C++'s stand: memory safe but optionally allows you to shoot
    // yourself in your foot
    let mut lower_bound = problems.lower_bound(std::ops::Bound::Included(arg));
    while !lower_bound.peek_next().is_none() {
      let next = lower_bound.next().unwrap();
      if !next.0.starts_with(arg) {
        break;
      }

      let input_file = File::open(next.1.input_file_path.to_string());
      if input_file.is_err() {
        eprintln!("Failed to open input file: {}", next.1.input_file_path);
        failure = true;
        continue;
      }
      let mut input = String::new();
      let _ = input_file.unwrap().read_to_string(&mut input);
      let received_answer = (next.1.solution)(input);
      if received_answer.is_err() {
        eprintln!("{}", received_answer.unwrap_err());
        failure = true;
        continue;
      }
      let received_answer = received_answer.unwrap();
      if write {
        let answer_file = File::options()
          .write(true)
          .create(true)
          .open(next.1.answer_file_path.to_string());
        if answer_file.is_err() {
          eprintln!("Failed to open answer file: {}", next.1.answer_file_path);
          failure = true;
          continue;
        }
        answer_file
          .unwrap()
          .write_all(received_answer.as_bytes())
          .unwrap();
        println!("Successfully written the answer for {}", next.0);
      } else if check {
        let answer_file = File::open(next.1.answer_file_path.to_string());
        if answer_file.is_err() {
          eprintln!("Failed to open answer file: {}", next.1.answer_file_path);
          failure = true;
          continue;
        }
        let mut answer = String::new();
        let _ = answer_file.unwrap().read_to_string(&mut answer);
        if received_answer != answer {
          eprintln!(
            r#"Solution to {} does not match the answer
Expected answer: {}
Got:             {}"#,
            next.0, answer, received_answer
          );
          failure = true;
          continue;
        }
        println!("PASS: {}", next.0);
      } else {
        println!("{}: {}", next.0, received_answer);
      }
    }
  }
  if failure {
    exit(EXIT_FAILURE);
  } else {
    exit(EXIT_SUCCESS);
  }
}
