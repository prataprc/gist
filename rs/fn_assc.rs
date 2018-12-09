fn main() {
    scoping_fn();
}

fn scoping_fn() {
    extern crate std;
    use std::i16::MAX;

    const X: u32 = 10;
    static Y: u32 = 20;

    mod level1 {
        pub const Z: u32 = 30;
    }

    #[derive(Debug)]
    struct T {
        a: u32
    };

    trait TT {
        fn as_float(&self) -> f64;
    }

    impl T {
        fn new(a: u32) -> T {
            T{a}
        }
    }

    impl TT for T {
        fn as_float(&self) -> f64 {
            f64::from(self.a)
        }
    }

    fn local_fn() -> bool {
        true
    }

    let t = T::new(200);
    println!("{} {} {}", X, Y, MAX);
    println!("{} {:?} {:e}", level1::Z, t, t.as_float());
    println!("{}", local_fn());
}
