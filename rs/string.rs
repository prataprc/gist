fn main() {
    let static_str = "hello world"; // &'static str
    println!("str: {}", static_str);

    let mut string = static_str.to_string(); // mut s: String
    string.push_str(", how are you");
    println!("string: {}", string);

    let static_str1 = &string; // :String  will coerce to :&str with &
    println!("str coerced: {}", static_str1);

    // println!("&str cannot be indexed {}", static_str1[0]); // FIXME

    // interpreting &str as bytes
    let static_str2 = "忠犬ハチ公";
    for b in static_str2.as_bytes() {
        print!("{} ", b);
    }
    println!("");

    // interpreting &str as chars
    for c in static_str2.chars() {
        print!("{} ", c);
    }
    println!("");

    let _dog = static_str2.chars().nth(1);

    // concatenating String and &str
    println!("{}",static_str.to_string() + &static_str1.to_string() + static_str2);
}
