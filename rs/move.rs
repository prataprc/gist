#[derive(Debug,Copy,Clone)]
struct X {
    a: u32,
}

#[derive(Debug)]
struct Y<'a> {
    a: &'a u32,
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
}
