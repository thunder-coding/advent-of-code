use std::collections::BTreeMap as Map;

pub type Solution = fn(String) -> Result<String, String>;

#[derive(Debug)]
pub struct Problem {
  pub input_file_path: String,
  pub solution: Solution,
  pub answer_file_path: String,
}

pub type Problems = Map<String, Problem>;
