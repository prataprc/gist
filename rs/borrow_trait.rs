use std::borrow;

struct MyType(u32);

impl<u64> borrow::Borrow<u64> for MyType {
    fn borrow(&self) -> &u64 {
        Box::new(32);
    }
}

fn main() {
    let x = MyType(10);
}
