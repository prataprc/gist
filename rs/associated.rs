#[derive(Debug)]
struct X {
    a: i32,
}

trait Typ {
    type Item;

    fn print(&self, x: Self::Item);
}

impl Typ for X {
    type Item = u32;

    fn print(&self, x: Self::Item) {
        println!("{}", x)
    }
}

impl Typ for X {
    type Item = u64;

    fn print(&self, x: Self::Item) {
        println!("{}", x)
    }
}

trait MyAdd<Rhs> {
    type Sum; // Sum is an *output*
    fn add(&self, Rhs) -> Self::Sum;
}

impl MyAdd<i32> for X {
    type Sum = f64;
    fn add(&self, rhs: i32) -> Self::Sum {
        (self.a + rhs) as f64
    }
}

impl<'a> MyAdd<&'a f64> for X {
    type Sum = i32;
    fn add(&self, rhs: &f64) -> Self::Sum {
        self.a + (*rhs as i32)
    }
}

trait Window {
    type Msg;

    fn notify(&self, Self::Msg) -> Result<(), String> {
        Ok(())
    }
}

impl Window for X {
    type Msg = u64;

    fn notify(&self, msg: u64) -> Result<(), String> {
        Ok(())
    }
}

fn main() {
    let x = X { a: 10 };
    println!("{:?}", x);
    x.add((&20).clone());

    let y: Box<dyn Window<Msg = u64>> = Box::new(X { a: 10 });
    y.notify(20);

    x.print(10_u32);
    x.print(20_u64);
}
