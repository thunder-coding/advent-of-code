pub struct Problem {
  pub year: i32,
  pub day: i8,
  pub part: i8,
}
pub type ProblemList = Vec<Problem>;

macro_rules! add_problems_for_day {
  ($problems_list:expr, $year:expr, $day:expr) => {
    $problems_list.push(Problem {
      year: $year,
      day: $day,
      part: 1,
    });
    $problems_list.push(Problem {
      year: $year,
      day: $day,
      part: 2,
    });
  };
}

macro_rules! add_problems_for_year {
  ($problems_list:expr, $year:expr) => {
    for day in 1..26 {
      add_problems_for_day!($problems_list, $year, day);
    }
  };
}

pub fn get_problems_list() -> ProblemList {
  let mut problems_list = ProblemList::new();
  add_problems_for_day!(problems_list, 2015, 1);
  add_problems_for_day!(problems_list, 2015, 2);
  add_problems_for_day!(problems_list, 2015, 3);
  return problems_list;
}
