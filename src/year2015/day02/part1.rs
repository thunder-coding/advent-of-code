use super::parse::parse;
pub fn part1(input: String) -> Result<String, String> {
  let boxes = parse(input);
  if boxes.is_err() {
    return Err(boxes.unwrap_err());
  }
  let mut wrapping_paper_area = 0;
  for curr_box in boxes.unwrap() {
    wrapping_paper_area += 3 * curr_box[0] * curr_box[1] + 2 * curr_box[2] * (curr_box[0] + curr_box[1]);
  }
  return Ok(wrapping_paper_area.to_string());
}
