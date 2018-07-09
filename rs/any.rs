#![feature(get_type_id)]

use std::any::Any;

fn main() {
    let a = &10;
    let any_a = a as &Any;
    println!("{}", any_a.is::<i32>());
    println!("{:?}", a.get_type_id());
}
