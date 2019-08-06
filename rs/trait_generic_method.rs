trait T {
    fn spec(&self) -> u32;

    fn spec1<X>(&self) -> u32
    where
        Self: Sized;

    fn gen<X: From<u32>>(&self) -> X
    where
        Self: Sized,
    {
        From::from(self.spec())
    }

    fn gen_consume<X: From<u32>>(self) -> X
    where
        Self: Sized,
    {
        From::from(self.spec())
    }
}

impl T for Box<dyn T> {
    fn spec(&self) -> u32 {
        (**self).spec()
    }
    fn spec1<X>(&self) -> u32
    where
        Self: Sized,
    {
        (**self).spec1()
    }
}

// okay
fn f(t: Box<dyn T>) -> u32 {
    t.spec()
}

fn g(t: Box<dyn T>) -> u32 {
    t.gen()
}

fn h(t: Box<dyn T>) -> u32 {
    t.gen_consume()
}

#[derive(Clone)]
struct O(u32);

impl T for O {
    fn spec(&self) -> u32 {
        self.0
    }
    fn spec1<X>(&self) -> u32 {
        self.0
    }
}

fn main() {
    println!("aa");
    f(Box::new(O(1)));
    println!("bb");
    g(Box::new(O(2)));
    println!("cc");
    h(Box::new(O(3)));
}
