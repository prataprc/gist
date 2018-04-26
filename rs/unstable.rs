#![feature(iterator_step_by)]

fn main() {
    for x in (0..8).step_by(2) {
        println!("{}", x)
    }
}
