fn main() {
    let mut x = 10;
    {
        let y = &x;
        let z = &x;
        // x = 20; not allowed because it already borrowed.
        println!("{} {} {}", x, y, z);
    }

    {
        let y = &mut x;
        // let z = &x; not allowed, only once it can be mutably borrowed
        // println!("{} {}", x, y); println borrows x.
        println!("{}", y);
    }

    //let x: &mut [i32] = &mut [0,1,2,3];
    //let y: &mut [i32] = &mut x[0..];
    //let z = &mut x[1..3];
    //println!("{:?}", x);
    //println!("{:?} {:?}", y, z);
}
