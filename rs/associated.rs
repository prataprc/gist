#[derive(Debug)]
struct X {
    a: i32
}

trait Add<Rhs> {
    type Sum; // Sum is an *output*
    fn add(&self, &Rhs) -> Sum;
}

impl Add<i32> for X {
    type Sum = f64;
    fn add(&self, rhs: &i32) -> Sum { (self.a+rhs) as f64 }
}

impl Add<f64> for X {
    type Sum = i32;
    fn add(&self, rhs: &f64) -> Sum { self.a + (rhs as i32) }
}

fn main() {
    let x = X{a: 10};
    println!("{:?}", x);
}
