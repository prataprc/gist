fn main() {
    let mut arr = vec![1, 2, 3, 4, 5, 6, 7];
    (0..2).for_each(|_| arr.push(arr.remove(0)));
    println!("{:?}", arr);
}
