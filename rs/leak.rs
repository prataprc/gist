struct Mytype {
    val: i32,
}

impl Drop for Mytype {
    fn drop(&mut self) {
        println!("dropping mytype");
    }
}

fn main() {
    let x = Mytype { val: 10 };
    noleak(x);
    let x = Mytype { val: 20 };
    leak(x);
}

fn noleak(x: Mytype) -> i32 {
    x.val
}

fn leak<'a>(x: Mytype) -> &'a mut Mytype {
    unsafe { &mut x }
}
