#[derive(Debug)]
pub enum Direction {
  North,
  South,
  East,
  West,
}

pub type Directions = Vec<Direction>;

pub fn parse(input: String) -> Result<Directions, String> {
  let mut directions = Directions::new();
  directions.reserve(input.len());
  for chr in input.chars() {
    match chr {
      '^' => {
        directions.push(Direction::North);
      }
      'v' => {
        directions.push(Direction::South);
      }
      '<' => {
        directions.push(Direction::East);
      }
      '>' => {
        directions.push(Direction::West);
      }
      _ => {
        return Err(format!(
          "Unexpected character '{}' when parsing input.txt",
          chr
        ));
      }
    }
  }
  return Ok(directions);
}
