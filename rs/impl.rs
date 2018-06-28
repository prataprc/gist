#[derive(Debug)]
struct X {
    a: u32,
    b: u32,
    c: u32,
}

impl X {
    const FOO: i32 = 1;

    fn add10(self) -> u32 {
        self.a + 10
    }
    fn add20(&self) -> u32 {
        self.b + 20
    }
    fn add30(&mut self) -> u32 {
        self.c += 30;
        self.c
    }
}

enum E {
    T(&'static str),
}

impl E {
    const FOO: i32 = 1;
}

fn main() {
    let m = X{a: 100, b: 200, c: 300};
    let a = m.add10(); // value is moved in the function call.
    println!("{}", a);
    let m = X{a: 100, b: 200, c: 300};
    let b = m.add20();
    println!("{} {:?} ", b, m);
    let mut m = X{a: 100, b: 200, c: 300};
    let c = m.add30();
    println!("{} {:?} ", c, m);
}
