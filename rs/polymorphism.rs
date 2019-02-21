struct Mytype<K> {
    a: K,
}

impl<K> Mytype<K> {
    fn render(&self) {
        unreachable!();
    }
}

impl Mytype<u64> {
    fn render(&self) {
        println!("i am u64");
    }
}

impl Mytype<String> {
    fn render(&self) {
        println!("i am u64");
    }
}

fn main() {
    let x: Mytype<u64> = Mytype { a: 10 };
    x.render();
}
