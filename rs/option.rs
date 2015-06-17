use std::mem;

fn main() {
    let mut x = Some(4_u64);
    println!("x size of: {} x: {:p} &x: {:?}", mem::size_of::<Option<u64>>(), &x, x);
    match x.as_mut() {
        Some(&mut ref mut v) => {*v = 42; println!("{:p} {}", v, v)},
        None => {},
    }
    println!("x size of: {} x: {:p} &x: {:?}", mem::size_of::<Option<u64>>(), &x, x);

    let ref mut y = 4;
    println!("y {:p} {}", y, y);
    match y {
        &mut ref mut v => {*v = 42; println!("{:p} {}", v, v)}
    }
    println!("y: {:p} &y: {:?}", &y, y);

    let z = &4;
    println!("z {:p} {}", z, z);
    match z {
        v => {println!("{:p} {}", v, v)}
    }
    println!("z: {:p} &z: {:?}", &z, z);

    let mut a = &4;
    println!("a {:p} {}", a, a);
    match a {
        &v => {println!("{} {}", v, v)}
    }
    println!("a: {:p} &a: {:?}", &a, a);
}
