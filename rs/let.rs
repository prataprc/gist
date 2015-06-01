#[derive(Debug)]
struct Foo {
    a: u64,
    b: u64,
}

struct Bar(u32, u8);

fn main() {
    let a = true;
    let x = 30;
    let y = &x;

    let m = Foo{a: 10, b:20};
    {
        let n = &m;
        let x = true;
        println!("x as {} is @ {:p}", x, &x);
        println!("n: moved struct Foo -- as {:?} is @ {:p}", n, &n);
    }

    println!("a as {} is @ {:p}", a, &a);
    println!("y as {} is @ {:p} / {:p}", y, y, &y);

    let bar = Bar(10, 20);
    // let Bar(a, 20) = bar; // refutable pattern not allowed

    match bar {
        Bar(a, 20) => println!("bar1({}, 20)", a), // refutable pattern allowed
        _ => (),
    };
}
