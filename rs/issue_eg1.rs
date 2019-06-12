// https://github.com/rust-lang/rust/issues/42721

use std::convert::From;

struct SomeError;
enum Error<E> {
    One(SomeError),
    Two(E),
}

/// impl<E> From<SomeError> for Error<E> where E: !SomeError {
impl<E> From<E> for Error<E> {
    fn from(error: E) -> Self {
        Error::One(error)
    }
}

impl<E> From<SomeError> for Error<E> {
    fn from(error: E) -> Self {
        Error::Two(error)
    }
}

fn main() {
    println!("hello world");
}
