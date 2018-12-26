#[derive(Debug,Copy,Clone)]
struct X(u128);

#[derive(Debug)]
struct Y(u128);

fn main() {
    let m = X(12);
    let n = m;
    println!("m: {:?} n: {:?}", m, n);

    let a = Y(14);
    let b = a;
    println!("b: {:?}", b);
}

