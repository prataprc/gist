fn main() {
    println!("main ...");
    let x = 1;
    println!("x: {}, &x: {:p}", x, &x);

    boxed();
    option_box();
    box_dereference();
    box_to_mutref();
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
    let y = Box::new(*x + 1);
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

fn box_dereference() {
    println!("box_dereference ...");
    let my_num: Box<i32> = Box::new(10);
    let my_num_ptr: *const i32 = &*my_num;
    let mut my_speed: Box<i32> = Box::new(88);
    let my_speed_ptr: *mut i32 = &mut *my_speed;
    println!("ref {:p} mut {:p}", my_num_ptr, my_speed_ptr);

    let my_speed_ref = &mut my_speed;
    println!("box reference {:?}", my_speed_ref);
    // println!("box {:?}", my_speed); <-- error, already borrowed as mutable
}

fn box_to_mutref() {
    println!("box_to_mutref ...");
    let mut my_num: Box<i32> = Box::new(10);
    let my_num_mut_ref: *mut i32 = &mut *my_num;
    let my_num_mut_ptr = &mut *my_num;

    println!("ref {:p} {:p}", my_num_mut_ref, my_num_mut_ptr);
}
