#[derive(Debug,Eq,PartialEq,PartialOrd,Ord)]
enum Json {
    Nil,
    Bool(bool),
    Integer(i128),
    String(String),
    Array(Vec<Json>),
}

#[derive(Debug)]
enum Other {
    Json,
    None,
}

fn main() {
    println!("");
    let a = Json::Nil;
    println!("{:?}", a);
    let a = Json::Bool(false);
    println!("{:?}", a);
    let a = Json::Integer(10);
    println!("{:?}", a);
    let a = Json::String(r#""hello world""#.to_string());
    println!("{:?}", a);
    let mut a = Vec::new();
    a.push(Json::Nil);
    a.push(Json::Bool(true));
    println!("{:?}", a);

    println!("ordering");
    let a = Json::Bool(true);
    let b = Json::Bool(false);
    let c = Json::Nil;
    println!("Bool(true) ord Bool(false) {:?}", a.cmp(&b));
    println!("Bool(false) ord Bool(true) {:?}", b.cmp(&a));
    println!("Nil ord Bool(true) {:?}", c.cmp(&a));
    println!("Nil ord Bool(false) {:?}", c.cmp(&b));


    println!("");
    let b = Other::None;
    println!("{:?}", b);
}
