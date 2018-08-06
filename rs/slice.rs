fn main() {
    let slice: &[i32] = &mut [0,1,2,3];
    let sls = &slice[1..3];
    println!("{:?}, {:?}", slice, sls);
    let mut itr: std::slice::Iter<i32> = slice.iter();
    let item = itr.next().unwrap();
    println!("{}", item);
    let v = vec![1,2,3,4, 5];
    let s: Vec<i32> = &v[1..3];
    println!("{:?}", s);
}
