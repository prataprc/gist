fn main() {
    let f = |s: &str| s.chars().next().unwrap();
    let s = "world".to_string();
    let fc = || "hello".to_string() + &s;
    println!("{}", f("hello"));
    println!("{}", fc());
}
