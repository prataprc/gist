fn main() {
    let mut x = 10;
    let y = &x;
    let z = &x;
    println!("{} {}", y, z);

    let x: &mut [i32] = &mut [0,1,2,3];
    let y: &mut [i32] = &mut x[0..];
    let z = &mut x[1..3];
    println!("{:?}", x);
    println!("{:?} {:?}", y, z);
}
