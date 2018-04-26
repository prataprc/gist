fn main() {
    let mut a: [i32; 3] = [1, 2, 3];
    assert_eq!(a.into_iter().nth(1), Some(&2));
    println!("{:?}", a);

    match a.iter().nth(0) {
        Some(x) => println!("{}", x),
        None => println!("None"),
    }
    println!("{:?}", a);

    let b = [7,8,9];
    for (i, item) in a.iter().chain(b.iter()).enumerate() {
        println!("{:?} {:?}", i, item);
    }
    println!("{:?}", a)
}
