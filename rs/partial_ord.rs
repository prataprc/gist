#[derive(PartialEq,PartialOrd,Default,Debug)]
struct X {
    a: u32,
    b: u32,
}

fn main() {
    let x = X{a: 10, b: 20};
    let y = X{a: 10, b: 20};
    println!("{:?}", x);
    println!("{}", x < y);
}
