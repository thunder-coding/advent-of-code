use std::fs::File;
use std::io::Write;
use std::process::exit;

use libc::EXIT_FAILURE;
mod problems;

fn main() {
  println!("cargo:rerun-if-changed=build.rs");
  println!("cargo:rerun-if-changed=src/utils/problems.rs");
  println!("cargo:rerun-if-changed=src/utils/get_problems.rs");
  let problems_rs = File::options()
    .write(true)
    .create(true)
    .truncate(true)
    .open("src/utils/get_problems.rs");
  if problems_rs.is_err() {
    println!("cargo::error=Failed to open src/utils/get_problems.rs for writing");
    exit(EXIT_FAILURE);
  }
  let mut problems_rs = problems_rs.unwrap();
  let mut problems_rs_content = String::new();
  problems_rs_content.push_str("use super::solutions::Problems;\n");
  problems_rs_content.push_str("use super::solutions::Problem;\n");
  problems_rs_content.push_str("pub fn get_problems() -> Problems {\n");
  problems_rs_content.push_str("  let mut problems = Problems::from_iter(vec![");

  for problem in problems::get_problems_list() {
    problems_rs_content.push_str(&format!(
      r#"    (
      "{}".to_string(),
      Problem {{
        input_file_path: "{}".to_string(),
        solution: {},
        answer_file_path: "{}".to_string(),
      }},
    ),
"#,
      format!("{}/{:02}/{}", problem.year, problem.day, problem.part),
      format!("src/year{}/day{:02}/input.txt", problem.year, problem.day),
      format!(
        "crate::year{}::day{:02}::part{}::part{}",
        problem.year, problem.day, problem.part, problem.part
      ),
      format!(
        "src/year{}/day{:02}/answer{}.txt",
        problem.year, problem.day, problem.part
      )
    ));
  }

  problems_rs_content.push_str("  ]);\n");
  problems_rs_content.push_str("  return problems;\n");
  problems_rs_content.push_str("}\n");
  if problems_rs
    .write_all(problems_rs_content.as_bytes())
    .is_err()
  {
    println!("cargo::error=Failed to write to src/utils/problems.rs");
    exit(EXIT_FAILURE);
  }
}
