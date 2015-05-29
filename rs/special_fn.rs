#[derive(Debug)]
struct GenTup<T>(T,);

fn value<u32>(x: GenTup<u32>) -> u32 {
    x.0
}

fn main() {
    let x = GenTup(10);
    value(x);
}
