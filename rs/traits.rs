use std::ops::Add;
//use std::borrow::Borrow;

/*********************
* operator overloading
* *******************/

#[derive(Copy,Clone,Debug)]
struct Foo<T>(T);

impl<T> Add for Foo<T> where T: Add {
    type Output=<T as std::ops::Add>::Output;

    fn add(self, rhs: Self) -> Self::Output {
        println!("Adding! by value");
        self.0 + rhs.0
    }
}

impl<'a, T> Add for &'a Foo<T> where T: Add {
    type Output=<T as std::ops::Add>::Output;

    fn add(self, rhs: &Foo<T>) -> Self::Output {
        println!("Adding! by reference");
        &self.0 + &rhs.0
    }
}

fn main() {
    let (x, y) = (Foo(10), Foo(20));
    println!("{:?} + {:?} {}", x, y, x + y);
    //println!("&Foo + Foo: {}", &x + &y);
}
