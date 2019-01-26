use std::ops::DerefMut;

fn main() {
    let mut x = Box::new(10_i128);
    println!("{:p}", x);
    let y: &mut i128 = x.deref_mut();
    let z: *const i128 = y as *const i128;
    let m: *mut i128 = y as *mut i128;
    let a = unsafe { Box::from_raw(m) };
    println!("{:p} {:p}", y, z);
    println!("{:p} {:p}", m, a);
}
