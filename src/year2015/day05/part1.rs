pub fn part1(input: String) -> Result<String, String> {
  let mut has_twice_letters = false;
  let mut has_naughty_pair = false;
  let mut vowel_count = 0;
  let mut nice_count = 0;
  let mut last_newline_index = 0;
  for index in 0..input.len() {
    match input.bytes().nth(index).unwrap() {
      b'\n' => {
        if vowel_count >= 3 && has_twice_letters && !has_naughty_pair {
          nice_count += 1;
        }
        last_newline_index = index;
        vowel_count = 0;
        has_naughty_pair = false;
        has_twice_letters = false;
        continue;
      }
      b'a' | b'e' | b'i' | b'o' | b'u' => {
        vowel_count += 1;
      }
      _ => {}
    }
    if index > last_newline_index + 1 {
      if input.bytes().nth(index).unwrap() == input.bytes().nth(index - 1).unwrap() {
        has_twice_letters = true;
      }
      match input.bytes().nth(index).unwrap() {
        b'b' | b'd' | b'q' | b'y' => {
          if input.bytes().nth(index).unwrap() - 1 == input.bytes().nth(index - 1).unwrap() {
            has_naughty_pair = true;
          }
        }
        _ => {}
      }
    }
  }
  if vowel_count >= 3 && has_twice_letters && !has_naughty_pair {
    nice_count += 1;
  }
  return Ok(nice_count.to_string());
}
