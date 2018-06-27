use std::env;

fn main() {
    println!("Hello prana, I am going to do division for you !");
    let arguments: Vec<String> = env::args().collect();
    let dividend: i32 = arguments[1].parse().unwrap();
    let divisor: i32 = arguments[2].parse().unwrap();
    let q = dividend / divisor;
    let r = dividend % divisor;
    println!("{} / {} result: quotient: {} reminder {}", dividend, divisor, q, r);
}
