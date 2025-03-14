use super::parse::parse;
pub fn part2(input: String) -> Result<String, String> {
  let boxes = parse(input);
  if boxes.is_err() {
    return Err(boxes.unwrap_err());
  }
  let mut ribbon_length = 0;
  for curr_box in boxes.unwrap() {
    ribbon_length += 2 * (curr_box[0] + curr_box[1]) + curr_box[0] * curr_box[1] * curr_box[2];
  }
  return Ok(ribbon_length.to_string());
}
