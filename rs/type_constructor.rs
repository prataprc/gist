#! /usr/bin/env rustr

#[derive(Debug)]
struct MyType<T> {
    x: T
}

#[derive(Debug)]
struct MyTypeOver<U> {
    y: MyType<U>
}

fn main() {
    let num = 10;
    let a = MyType{x: &num};
    let b = MyType{x: vec![1,2]};
    println!("{:?}", a);
    println!("{:?}", b);

    let m = MyTypeOver{y: a};
    println!("{:?}", m);
}
