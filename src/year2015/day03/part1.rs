use std::collections::HashSet;

use super::common::Coordinate;
use super::parse::{Direction, parse};
pub fn part1(input: String) -> Result<String, String> {
  let directions = parse(input);
  if directions.is_err() {
    return Err(directions.unwrap_err());
  }
  let directions = directions.unwrap();
  let mut santa_pos = Coordinate { x: 0, y: 0 };
  let mut positions: HashSet<Coordinate> = HashSet::new();
  positions.insert(santa_pos);

  for direction in directions {
    match direction {
      Direction::North => santa_pos.y += 1,
      Direction::South => santa_pos.y -= 1,
      Direction::East => santa_pos.x += 1,
      Direction::West => santa_pos.x -= 1,
    }
    positions.insert(santa_pos);
  }
  return Ok(positions.len().to_string());
}
