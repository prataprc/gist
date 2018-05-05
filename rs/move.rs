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
    println!("{:?} {:?}", m, n);

    let o = 10;
    {
        let m = Y{a: &o};
        let n = m;
        println!("{:?}", n);
    }
}
