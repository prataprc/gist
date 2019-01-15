fn main() {
    let mut x = 10;
    let mut y = 20;
    asparam(&mut x, &mut y);
}

fn asparam<'a>(mut arg: &'a mut i32, arg1: &'a mut i32) {
    arg = arg1;
    println!("{}", arg);
}
