trait Foo {
    fn method(&self) -> String;
}

impl Foo for u8 {
    fn method(&self) -> String { format!("u8: {}", self) }
}

impl Foo for String {
    fn method(&self) -> String { format!("String: {}", self) }
}

fn do_something_static<T: Foo>(x: T) -> String {
    x.method()
}

fn do_something_dynamic(x: &Foo) -> String {
    x.method()
}

fn main() {
    println!("{}", do_something_static(1));
    println!("{}", do_something_static("hello".to_string()));
    println!("{}", do_something_dynamic(&5));
    println!("{}", do_something_dynamic(&"world".to_string()));
}
