#![feature(core)]

#[derive(Debug)]
struct Other<T>(T, T, T);

type MyType<T> = Other<T>;

fn main() {
    let x: MyType<u32> = Other(19, 29, 20);
    println!("my type {:?}", x);
}
