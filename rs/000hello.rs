fn main() {
    let mut x = vec!["hello", "world"];
    println!("{:?}", x);

    x[0] = "okay";
    println!("{:?}", x);

    x.push("foo");
    println!("{:?}", x);
}
