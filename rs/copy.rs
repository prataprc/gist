#[derive(Debug,Copy,Clone)]
struct MyDerived {
    a: u64,
    b: u64,
    c: u64,
    d: u64,
}

#[derive(Debug,Copy)]
struct My {
    a: u64,
    b: u64,
    c: u64,
    d: u64,
}

impl Clone for My {
    fn clone(&self) -> My {
        *self
    }
}

fn main() {
    //accplain()
    //accmyderived()
    accmy()
}

#[allow(dead_code)]
fn accplain() {
    let mut acc = 0u64;
    for _i in 1..100000000 {
        acc += 10;
    }
    println!("plain acc: {}", acc);
}

#[allow(dead_code)]
fn accmyderived() {
    let x = MyDerived{a: 10, b:20, c: 30, d: 40};
    let mut acc = 0u64;
    for _i in 1..100000000 {
        let y = x;
        acc += y.a;
    }
    println!("{:?} acc: {}", x, acc);
}

#[allow(dead_code)]
fn accmy() {
    let x = My{a: 10, b:20, c: 30, d: 40};
    let mut acc = 0u64;
    for _i in 1..100000000 {
        let y = x;
        acc += y.a;
    }
    println!("{:?} acc: {}", x, acc);
}
