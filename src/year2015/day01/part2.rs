pub fn part2(input: String) -> String {
  let mut floor = 0;
  for i in 0..input.len() {
    match input.chars().nth(i).unwrap() {
      '(' => floor += 1,
      ')' => floor -= 1,
      _ => unreachable!("Invalid character encountered while reading input.txt"),
    }
    if floor == -1 {
      return (i + 1).to_string();
    }
  }
  unreachable!("Santa never reached the basement")
}
