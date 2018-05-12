use std::time;

fn main() {
    let mut array  = [0,1,2,3];
    println!("{:?}", array);
    let slice = &array;
    println!("{:?}", slice);
    let slice = &array[1..];
    println!("{:?}", slice);
    //let item: i32 = array[0];
    //println!("{:?}, {:?}", array, item);
    //let sls: &mut [i32] = &mut array[1..3];
    //sls[0] = 20;
    //let item: i32 = sls[0];
    //println!("{:?}, {:?}", sls, item);

    // initialized array
    //let x = num();
    //let y = [20; 2];
    //println!("{} {:?}", x, y);
}

fn num() -> u32 {
    let now = time::Instant::now();
    return now.elapsed().subsec_nanos()
}
