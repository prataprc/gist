#[derive(Debug)]
struct Person {
    name: Option<String>,
}

fn main() {
    let name = "Steve".to_string();
    let x: Option<Person> = Some(Person { name: Some(name) });
    match x {
        Some(Person { name: a @ Some(_), .. }) => println!("{:?}", a),
        _ => {}
    }
}
