#[derive(Debug)]
struct Foo {
    vec: Vec<String>,
}

fn main() {
    let mut foo = Foo {
        vec: vec!["Hello".to_string()],
    };
    let foo1 = &mut foo;
    let vec = &mut foo1.vec; // this doesn't work
                             // but with    foo1.vec - works fine
    vec.push("World".to_string());
    foo1.vec.push("Lorem".to_string());
    println!("{:?}", foo1);
}
