#![feature(custom_derive)] // for Borrow trait

use std::ops::Add;

/*********************
* operator overloading
* *******************/

#[derive(Copy, Clone, Debug, Borrow)]
struct Foo(u8);

impl Add for Foo {
    type Output = u8;

    fn add(self, _rhs: Foo) -> Self::Output {
        println!("Adding! by value");
        self.0 + self.0
    }
}

impl<'a> Add for &'a Foo {
    type Output = u8;

    fn add(self, _rhs: &Foo) -> Self::Output {
        println!("Adding! by reference");
        (*self).0 + (*self).0
    }
}

fn main() {
    let (x, y) = (Foo(10), Foo(20));
    println!("Foo + Foo: {}", x + y);
    println!("&Foo + Foo: {}", &x + &y);
}
