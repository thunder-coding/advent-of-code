use std::cell::RefCell;
use std::collections::HashSet;
use std::rc::Rc;

use super::common::Coordinate;
use super::parse::{Direction, parse};

pub fn part2(input: String) -> Result<String, String> {
  let directions = parse(input);
  if directions.is_err() {
    return Err(directions.unwrap_err());
  }
  let directions = directions.unwrap();
  let santa_pos = Rc::new(RefCell::new(Coordinate { x: 0, y: 0 }));
  let robot_pos = Rc::new(RefCell::new(Coordinate { x: 0, y: 0 }));
  let mut curr_pos = Rc::clone(&robot_pos);
  let mut positions: HashSet<Coordinate> = HashSet::new();
  positions.insert(*santa_pos.borrow());

  for direction in directions {
    if Rc::as_ptr(&curr_pos) == Rc::as_ptr(&robot_pos) {
      curr_pos = Rc::clone(&santa_pos);
    } else {
      curr_pos = Rc::clone(&robot_pos);
    }
    match direction {
      Direction::North => curr_pos.borrow_mut().y += 1,
      Direction::South => curr_pos.borrow_mut().y -= 1,
      Direction::East => curr_pos.borrow_mut().x += 1,
      Direction::West => curr_pos.borrow_mut().x -= 1,
    }
    positions.insert(*curr_pos.borrow());
  }
  return Ok(positions.len().to_string());
}
