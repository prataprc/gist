fn main() {
    println!("{}", pattern((20,10)));
}

fn pattern((x, y): (u32, u32)) -> u32 {
    match y {
        2 => x >> 1,
        _ => x/y
    }
}
