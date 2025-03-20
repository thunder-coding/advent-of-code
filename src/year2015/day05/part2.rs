use std::collections::HashMap;

pub fn part2(input: String) -> Result<String, String> {
  let mut has_repeating_pair = false;
  let mut has_repeat_with_sep = false;
  let mut nice_count = 0;
  let mut pairs: HashMap<[u8; 2], usize> = HashMap::new();
  let mut last_newline_index = 0;

  for index in 0..input.len() {
    match input.bytes().nth(index).unwrap() {
      b'\n' => {
        if has_repeating_pair && has_repeat_with_sep{
          nice_count += 1;
        }
        has_repeating_pair = false;
        has_repeat_with_sep = false;
        pairs.clear();
        last_newline_index = index;
      }
      _ => {
        if index >= last_newline_index + 2 {
          let find = pairs.iter().find(|&elem| {
            return elem.0[0] == input.bytes().nth(index).unwrap() && elem.0[1] == input.bytes().nth(index - 1).unwrap();
          });
          if find != None {
            if *find.unwrap().1 <= index - 2 {
              has_repeating_pair = true;
            }
          } else {
            pairs.insert([input.bytes().nth(index).unwrap(), input.bytes().nth(index - 1).unwrap()], index);
          }
        }

        if index >= last_newline_index + 3 && input.bytes().nth(index).unwrap() == input.bytes().nth(index - 2).unwrap() {
          has_repeat_with_sep = true;
        }
      }
    }
  }
  if has_repeating_pair && has_repeating_pair {
    nice_count += 1;
  }
  return Ok(nice_count.to_string());
}
