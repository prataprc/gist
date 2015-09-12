trait MyPartialEq<Rhs: ?Sized = Self> {
    /// This method tests for `self` and `other` values to be equal, and is used by `==`.
    #[stable(feature = "rust1", since = "1.0.0")]
    fn myeq(&self, other: &Rhs) -> bool;
}

type X = u32;

impl MyPartialEq for X {
    fn myeq(&self, other: &X) -> bool {
        ((*self) as u32) == ((*other) as u32)
    }
}

fn main() {
    let (x, y): (X, X) = (10, 20);
    println!("x: {:?}, y: {:?}", x, y);
    println!("x == y: {}", x.myeq(y));
}
