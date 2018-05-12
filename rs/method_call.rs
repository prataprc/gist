struct MyBox<T>(T);

trait MyTrait<T> {
    fn print(x: T);
}

impl<T> MyBox<T> {
    fn new(x: T) -> MyBox<T> {
        MyBox(x)
    }
}

impl<T> MyTrait<T> for MyBox<T> {
    fn print(x: T) {
        println!("self");
    }
}

use std::ops::Deref;

impl<T> Deref for MyBox<T> {
    type Target = T;

    fn deref(&self) -> &T {
        &self.0
    }
}

fn main() {
    let x = 5;
    let y = MyBox::new(x);

    y.print();
}
