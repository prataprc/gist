static x: &'static str = "hello";

fn main() {
    println!("called {}", myfunc("world"));
}

fn myfunc(y: &str) -> &'static str {
    println!("{}", y);
    x
}
