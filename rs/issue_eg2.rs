#![crate_type = "lib"]

use std::marker::PhantomData;

trait Foo {
    type Type: Qux<Self>;
}

struct Bar<T>(PhantomData<T>);

trait Qux<T> {}

impl<T: Foo<Type = U>, U: Qux<T>> From<U> for Bar<T> {
    fn from(t: U) -> Self {
        Bar(PhantomData)
    }
}

fn main() {
    println!("hello world");
}
