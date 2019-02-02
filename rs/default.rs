use std::sync::Arc;

#[derive(Default, Debug)]
struct Mytype {
    val: i128,
    next: Option<Arc<Mytype>>,
}
fn main() {
    let a: Mytype = Default::default();
    println!("{:?}", a);
}
