struct Mytype {
    value: u32,
}

impl Mytype {
    fn get(&self) -> u32 {
        self.value
    }

    fn get(&mut self) -> u32 {
        self.value
    }
}

fn main() {
    let x = Mytype { value: 10 };
}
