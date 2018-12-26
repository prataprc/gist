#[derive(Debug,Copy,Clone)]
struct X {
    a: u32,
}

#[derive(Debug)]
struct Y<'a> {
    a: &'a u32,
}

#[derive(Debug)]
struct Z {
    a: i128,
}

fn main() {
    let m = X{a: 10};
    let n = m;
    println!("for type X m and n {:?} {:?}", m, n);

    let o = 10;
    {
        let m = Y{a: &o};
        println!("for type Y address of m {:p}", &m);
        let n = m;
        println!("for type Y address of n {:p}", &n);
    }

    let x = 10;
    let y = x;
    println!("{} {}", x, y);

    check_address()
}

fn check_address() {
    let z = Z{a: 10};
    println!("check_address {:p}", &z);
    inner(z)
}

fn inner(x: Z) {
    println!("inner {:p}", &x);
}
