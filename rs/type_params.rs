type X<T> = (u32, T);

fn main() {
    let x: X<i8> = (10, 20);
    println!("{:?}", x);
}
