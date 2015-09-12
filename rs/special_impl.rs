struct GenTup<T>(T,);

// impl of GenTup specialized to `i32`
impl GenTup<i32> {
    fn value(&self) -> &i32 {
        let &GenTup (ref val) = self;
        val
    }
}

// impl of GenTup specialized to `f64`
impl GenTup<f64> {
    fn value(&self) -> &f64 {
        let &GenTup (ref val) = self;
        val
    }
}

fn main() {
    let x = GenTup(3.0f64);
    let y = GenTup(3i32);

    println!("{}, {}", x.value(), y.value());
}
