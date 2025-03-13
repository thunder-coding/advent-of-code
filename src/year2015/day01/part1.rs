pub fn part1(input: String) -> String {
  let mut floor = 0;
  for chr in input.chars() {
    match chr {
      '(' => floor += 1,
      ')' => floor -= 1,
      _ => unreachable!("Invalid character encountered while reading input.txt"),
    }
  }
  return floor.to_string();
}
