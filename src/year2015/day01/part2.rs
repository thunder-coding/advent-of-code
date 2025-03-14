pub fn part2(input: String) -> Result<String, String> {
  let mut floor = 0;
  for i in 0..input.len() {
    match input.chars().nth(i).unwrap() {
      '(' => floor += 1,
      ')' => floor -= 1,
      _ => {
        return Err("Invalid character encountered while reading input.txt".to_string());
      }
    }
    if floor == -1 {
      return Ok((i + 1).to_string());
    }
  }
  return Err("Santa never reached the basement".to_string());
}
