#[derive(Debug)]
struct X(u32);

fn main() {
    let x = X(10);
    let y = &x;
    let z = *y;
    println!("{:?}", x);
    println!("{:?}", y);
    println!("{:?}", z);
}
