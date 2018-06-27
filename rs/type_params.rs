use std::ops::Add;

type X<T> = (u32, T);

fn main() {
    let x: X<i8> = (10, 20);
    println!("{:?}", x);
}

fn function1<T>(a: T) -> <T as Add>::Output where T: Add + Default {
    let b: T = T::default();
    return a+b
}
