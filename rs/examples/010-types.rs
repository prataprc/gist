
fn main() {
    //--- primitive types
    // sizeof_numbers
    println!("size of i8  {}", std::mem::size_of::<i8>());
    println!("size of u8  {}", std::mem::size_of::<u8>());
    println!("size of i16 {}", std::mem::size_of::<i16>());
    println!("size of u16 {}", std::mem::size_of::<u16>());
    println!("size of i32 {}", std::mem::size_of_val(&1_i32));
    println!("size of u32 {}", std::mem::size_of_val(&1_u32));
    println!("size of i64 {}", std::mem::size_of_val(&1_i64));
    println!("size of u64 {}", std::mem::size_of_val(&1000_000_u64));
    println!("size of f32 {}", std::mem::size_of_val(&1_f32));
    println!("size of f64 {}", std::mem::size_of_val(&1_f64));
    // sizeof_boolean
    println!("size of true  {}", std::mem::size_of_val(&true));
    println!("size of false {}", std::mem::size_of_val(&false));
    // sizeof_char
    println!("size of char  {}", std::mem::size_of_val(&'1'));
    // sizeof_unit
    println!("size of unit  {}", std::mem::size_of_val(&()));
    // sizeof_pointers
    println!("size of isize  {}", std::mem::size_of_val(&1_isize));
    println!("size of usize  {}", std::mem::size_of_val(&1_usize));

    // str
    // tuple
    // array
    // slice

    // casting
    let decimal = 650.123_f32;
    let x: u8 = decimal as u8; // is how casting is done.
    println!("casting {} as {}", decimal, x);

    // use under-score to improve readability.
    println!("One million is written as {}", 1_0000_000u32);
    println!("defult integer is i32");
    println!("defult float is f64");
}
