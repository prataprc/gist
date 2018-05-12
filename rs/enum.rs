type Array<'a>=Vec<Json<'a>>;

type Object<'a>=Vec<(&'a str,Json<'a>)>;

#[derive(Debug)]
enum Json<'a> {
    Nil,
    True,
    False,
    Num(&'a str),
    Str(&'a str),
    Array,
    Object,
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
    let a = Json::True;
    println!("{:?}", a);
    let a = Json::False;
    println!("{:?}", a);
    let a = Json::Num("10");
    println!("{:?}", a);
    let a = Json::Str(r#""hello world""#);
    println!("{:?}", a);
    let mut a: Array = Vec::new();
    a.push(Json::Nil);
    a.push(Json::True);
    println!("{:?}", a);
    let mut a: Object = Vec::new();
    a.push(("key1", Json::Nil));
    a.push(("key2", Json::False));
    println!("{:?}", a);

    println!("");
    let b = Other::None;
    println!("{:?}", b);
}
