fn main() {
    let x = Box::new(5);
    let y = add_one_transfer_ownership(x);
    println!("{}", y);

    let mut a = 10;
    add_one_borrow(&mut a);
    println!("{}", a);
}

fn add_one_transfer_ownership(mut num: Box<i32>) -> Box<i32> {
    *num += 1;
    num
}

fn add_one_borrow(num: &mut i32) {
    *num += 1;
}
