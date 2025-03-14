pub type Box = [u32; 3];
pub type Boxes = Vec<Box>;

pub fn parse(input: String) -> Result<Boxes, String> {
  let mut boxes = Boxes::new();
  let mut current_box: Box = [0, 0, 0];
  let mut side_index = 0;
  for chr in input.chars() {
    match chr {
      '0'..='9' => {
        current_box[side_index] *= 10;
        current_box[side_index] += (chr as u32) - ('0' as u32);
      }
      'x' => {
        side_index += 1;
        if side_index == 3 {
          return Err(format!(
            "A cuboid is supposed to have only 3 sides on line {}",
            boxes.len() + 1
          ));
        }
      }
      '\n' => {
        if side_index == 2 {
          side_index = 0;
          current_box.sort();
          boxes.push(current_box);
          let mut index = 0;
          while index < current_box.len() {
            current_box[index] = 0;
            index += 1;
          }
        } else {
          return Err(format!(
            "Expected three sides, found only {} when parsing input.txt on line {}",
            side_index + 1,
            boxes.len() + 1
          ));
        }
      }
      _ => {
        return Err(format!(
          "Unexpected character at line {} when parsing input.txt",
          boxes.len() + 1
        ));
      }
    }
  }
  if side_index == 0 {
  } else if side_index == 2 {
    current_box.sort();
    boxes.push(current_box);
  } else {
    return Err(format!(
      "Expected three sides, found only {} when parsing input.txt on line {}",
      side_index + 1,
      boxes.len() + 1
    ));
  }
  return Ok(boxes);
}
