use std::io;

fn main() {
    let ref stdin: io::Stdin = io::stdin();
    println!("reference {:p}", stdin);
    println!("pointer to reference {:p}", &stdin);
    println!("boxed heap at {:p}", Box::new(10));

    refs();
}

fn refs() {
    let x = &10;
    let ref y = x;
    println!("x={:p} &x={:p}, y={:p}, &y={:p}", x, &x, y, &y);
}
