#[allow(dead_code)]
enum Option<T> {
    Value(T),
    Missing,
}

fn main() {
    let x = Option::Value(59.5);
    match x {
        Option::Value(i) if i > 5.0 => println!("Got an int bigger than five!"),
        Option::Value(..) => println!("Got an int!"),
        Option::Missing => println!("No such luck."),
    }
}
