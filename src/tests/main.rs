use std::fs::File;
use std::io::Read;
use std::process::exit;
extern crate advent_of_code;
use advent_of_code::utils::get_problems::get_problems;

macro_rules! error {
  ($failed:expr, $($arg:tt)*) => {
    eprintln!($($arg)*);
    $failed = true;
    continue;
  }
}

fn main() {
  let mut failure = false;
  let problems = get_problems();
  for problem in problems {
    let input_file = File::open(problem.1.input_file_path.to_string());
    if input_file.is_err() {
      error!(
        failure,
        "Failed to open input file: {}", problem.1.input_file_path
      );
    }
    let mut input = String::new();
    let _ = input_file.unwrap().read_to_string(&mut input);
    let received_answer = (problem.1.solution)(input);
    if received_answer.is_err() {
      eprintln!("{}", received_answer.unwrap_err());
      failure = true;
      continue;
    }
    let received_answer = received_answer.unwrap();
    let answer_file = File::open(problem.1.answer_file_path.to_string());
    if answer_file.is_err() {
      error!(
        failure,
        "Failed to open answer file: {}", problem.1.answer_file_path
      );
    }
    let mut answer = String::new();
    let _ = answer_file.unwrap().read_to_string(&mut answer);
    if received_answer != answer {
      error!(
        failure,
        r#"Solution to {} does not match the answer
Expected answer: {}
Got:             {}"#,
        problem.0,
        answer,
        received_answer
      );
    }
    println!("PASS: {}", problem.0);
  }
  if failure {
    exit(libc::EXIT_FAILURE);
  }
  exit(libc::EXIT_SUCCESS);
}
