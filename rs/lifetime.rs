//static x: = "hello world";

fn main() {
    let s = "hello world".to_string();
    let s1: &str = &s[1..];
    let s2: &str = &s[2..];
    println!("{} {}", s1, s2);
    println!("{}", longest(s1, s2));
}

fn longest<'a, 'b>(x: &'a str, y: &'b str) -> &'a str {
    if x.len() > y.len() {
        x
    } else {
        y
    }
}
