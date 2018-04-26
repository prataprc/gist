fn main() {
    let mut cached: Vec<u32> = newvec();
    cached.push(2);
    println!("{:?}", cached);

    //let mut v = vec![1, 2, 3, 4, 5];
    //for i in &v {
    //    println!("A reference to {}", i);
    //}
    //for i in &mut v {
    //    println!("A mutable reference to {}", i);
    //}
    //for i in v {
    //    println!("Take ownership of the vector and its element {}", i);
    //}
}

fn newvec<T>() -> Vec<T> {
    let mut cached: Vec<T> = Vec::with_capacity(1000);
    cached.push(2);
    return cached
}
