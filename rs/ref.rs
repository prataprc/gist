use std::io;

fn main() {
    let ref stdin: io::Stdin = io::stdin();
    println!("stack is at {:p}", stdin);
    println!("boxed heap at {:p}", Box::new(10));
}
