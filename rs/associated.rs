#[derive(Debug)]
struct X {
    a: i32
}

trait MyAdd<Rhs> {
    type Sum; // Sum is an *output*
    fn add(&self, Rhs) -> Self::Sum;
}

impl MyAdd<i32> for X {
    type Sum = f64;
    fn add(&self, rhs: i32) -> Self::Sum { (self.a+rhs) as f64 }
}

impl<'a> MyAdd<&'a f64> for X {
    type Sum = i32;
    fn add(&self, rhs: &f64) -> Self::Sum { self.a + (*rhs as i32) }
}

fn main() {
    let x = X{a: 10};
    println!("{:?}", x);
    x.add((&20).clone());
}
