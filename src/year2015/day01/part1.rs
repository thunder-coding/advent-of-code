pub fn part1(input: String) -> Result<String, String> {
  let mut floor = 0;
  for chr in input.chars() {
    match chr {
      '(' => floor += 1,
      ')' => floor -= 1,
      _ => {
        return Err("Invalid character encountered while reading input.txt".to_string());
      }
    }
  }
  return Ok(floor.to_string());
}
