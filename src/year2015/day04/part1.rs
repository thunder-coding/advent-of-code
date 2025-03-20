use crate::helpers::md5::MD5;

pub fn part1(input: String) -> Result<String, String> {
  let mut i: u64 = 0;
  loop {
    let mut hasher = MD5::new();
    hasher.consume(input.clone().into());
    hasher.consume(i.to_string().into());
    let hash = hasher.compute();
    if hash[0] == 0x00 && hash[1] == 0x00 && (hash[2] & 0xF0) == 0x00 {
      return Ok(i.to_string());
    }
    if i == u64::MAX {
      break;
    }
    i += 1;
  }
  return Err("Exhausted all 64 bit unsigned integers while mining block".to_string());
}
