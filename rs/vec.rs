#[derive(Debug)]
struct MyT {
    a: i32,
}
fn main() {
    let mut w = Vec::new(); // return Vec<T>
    w.push(10); // type inference works within blocks.
    println!("after push {:?}", w);

    let w = vec![1,2,3];
    let x: i32 = w[1];
    println!("indexing into Vec<T> {} {:?}", x, w);

    //error[E0507]: cannot move out of indexed content
    //let w = vec![MyT{a:10}, MyT{a:20}];
    //let x = w[0];
    //println!("indexing that does not have Copy {:?} {:?}", x, w);

    let v = vec![100, 32, 57];
    for i in &v {
        println!("iterating vector {}", i);
    }


    //let mut cached: Vec<u32> = newvec::<u32>();
    //cached.push(2);
    //println!("{:?}", cached);

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

//fn newvec<T>() -> Vec<T> {
//    let mut cached: Vec<T> = Vec::with_capacity::<T>(1000);
//    cached.push(2);
//    return cached
//}
