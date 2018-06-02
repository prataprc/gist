extern crate clocksource;

fn main() {
    let clock = clocksource::new();
    println!("{}", clock.reference())
}
