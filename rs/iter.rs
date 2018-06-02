fn main() {
    let slice: &[i32] = &[0,1,2,3];
    let xx: Vec<&i32> = slice.iter().take_while(|&&p| p == 0).collect();
    println!("{:?}", xx);

    let array: [i32; 4] = [1,1,2,3];
    let xx: Vec<i32> = array.iter().map(|&p| p * 1).collect();
    println!("{:?}", xx);
    let iter = array.iter();
    println!("{:?}", iter);
}
