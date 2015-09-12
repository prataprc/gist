use std::ops::Add;

// first order generic type defined over type parameter T.
struct X<T: Add>(T,);

fn add<T: Add>(x: X<T>, y: X<T>) -> T::Output {
    (x.0 + y.0) as T::Output
}

fn main() {
    println!("{}", add(X(10), X(10)));
    println!("{}", add(X(&10_u16), X(&10_u16)));
}
