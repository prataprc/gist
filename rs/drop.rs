#[derive(Default)]
struct X {
    a: u64,
    b: i64,
}

fn main() {
    let x = X::default();
    std::mem::drop(x.a);
}
