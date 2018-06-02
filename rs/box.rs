fn main() {
    let x = Box::new(5);
    let y = add_one_transfer_ownership(&x);
    println!("x: {:p}, &x: {:p}", x, &x);
    println!("y: {:p}, &y: {:p}", y, &y);

    let z = x; // moved here.
    println!("move x: {}", z);

    let mut a = 10;
    add_one_borrow(&mut a);
    println!("{}", a);

    borrow_box();
}

fn add_one_transfer_ownership(num: &Box<i32>) -> Box<i32> {
    println!("add_one_transfer_ownership: num: {:p}, &num: {:p}", num, &num);
    Box::new(**num + 1)
}

fn add_one_borrow(num: &mut i32) {
    *num += 1;
}

fn borrow_box() {
    let x = Box::new(5);

    let z: &Box<i32> = &x;
    println!("borrowes as &Box<i32>: {}", z);

    let z: &i32 = &x;
    println!("borrow as &i32: {}", z);
}
