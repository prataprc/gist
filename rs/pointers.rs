fn main() {
    println!("main ...");
    let x = 1;
    println!("x: {}, &x: {:p}", x, &x);

    boxed();
    option_box();
}

fn boxed() {
    println!("box ...");
    let x: Box<i32> = Box::new(34);
    println!("x: {}, box_x: {:p}, &box_x: {:p}", x, x, &x);
    moved_box(x);
}

fn moved_box(x: Box<i32>) -> Box<i32> {
    println!("moved box ...");
    println!("x: {}, box_x: {:p}, &box_x: {:p}", x, x, &x);
    let y = Box::new(*x+1);
    println!("y: {}, box_y: {:p}, &box_y: {:p}", y, y, &y);
    y
}

fn option_box() {
    println!("option box ...");
    let n: Option<Box<i32>> = None;
    let s = Some(Box::new(34));
    println!("none: {:?}, &box_none: {:p}", n, &n);
    println!("some: {:?}, &box_some: {:p}", s, &s);
}
