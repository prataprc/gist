#![feature(copy_within)]

fn main() {
    let mut src = vec![0, 1, 2, 3, 4, 5, 6, 7];
    src.resize(12, 0);
    println!("{:?}", src);
    src.copy_within(..8, 4);
    println!("{:?}", src);
}
