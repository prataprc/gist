fn main() {
    let mut x = 10;
    {
        let mut y = &mut x;
        let mut z = &mut y;
        three_indirect(&mut z);
    }
    basic();
    print(&mut x);

    //println!("x: {}-{:p}, y: {}-{:p}-{:p}, z: {}-{:p}-{:p}", x, &x, y, y, &y, z, z, &z);
    //println!("take_as_immutable: {}", take_as_immutable(&10));
    //println!("take_as_mutable: {}", take_as_mutable(&mut 10));
}

fn basic() {
    let mut x = 5;
    {
        let y = &mut x; // -+ &mut borrow starts here
        *y += 1; //  |
    } // -+ ... and ends here
    let y = &mut x;
    x = 10;
    println!("basic {}", y);
}

//fn take_as_immutable(x: &i32) -> i32 {
//    let y = *x + 20;
//    y
//}
//
//fn take_as_mutable(x: &mut i32) -> &i32 {
//    *x = *x + 2;
//    x
//}

fn three_indirect(a: &mut (&mut (&mut i32))) {
    ***a = ***a + 1
}

fn print(x: &mut i32) {
    println!("print x: {}", x);
}
