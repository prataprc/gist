#![feature(box_syntax)]

// There is no copy in this code. main allocates enough room for the
// box, passes a pointer to that memory into foo as x, and then foo
// writes the value straight into the Box<T>.

#[allow(dead_code)]
struct BigStruct {
    one: i32,
    two: i32,
    // etc
    one_hundred: i32,
}

fn foo(x: Box<BigStruct>) -> BigStruct {
    *x
}

fn main() {
    let x = Box::new(BigStruct {
        one: 1,
        two: 2,
        one_hundred: 100,
    });
    println!("x: {:p}, &x: {:p}", x, &x);
    let y: Box<BigStruct> = box foo(x);
    println!("y: {:p}, &y: {:p}", y, &y);
}
