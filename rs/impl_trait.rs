use std::fmt::Display;

fn main() {
    asparam(1);
}

fn asparam<T>(arg: T)
where
    T: Display,
{
    println!("{}", arg);
}
