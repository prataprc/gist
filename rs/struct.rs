#[derive(Debug)]
struct X {
    a: u32,
}

mod xyz {
    static x: u32 = 20;
}

impl X {
    const x: u32 = 10;
    static x: u32 = 20;
}

fn main() {
    let x = X{a: 200};
    println!("{:?}", x);
}
