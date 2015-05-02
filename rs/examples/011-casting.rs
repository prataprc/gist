// no implicit type conversion (coercion) between primitive types.
// explicit type conversion (casting) can be performed using the `as` keyword.

fn main() {
    let decimal = 65.4321_f32;

    // let integer: u8 = decimal; FIXME: Error! no implicit conversion

    // explicit type converstion
    let integer = decimal as u8;
    let character = integer as char;

    println!("Casting: {} -> {} -> {}", decimal, integer, character);

    // when casting any value to an unsigned type, T,
    // std::T::MAX + 1 is added or subracted until the value
    // fits into the new type.

    // 1000 already fits in u18
    println!("1000 as a u16 is {}", 1000 as u16);

    // 1000 - 256 - 256 - 256 = 232
    println!("1000 as a u8 is : {}", 1000u16 as u8);
    // -1 + 256 = 255
    println!("-1 as a u8 is : {}", -1i8 as u8);

    // For positive numbers, this is same as the modulus.
    println!("1000 % 256 is : {}", 1000 % 256);

    // When casting to a signed type, the result is the same
    // as first casting to the corresponding unsigned type then
    // taking the two's complement.

    // unless it already fits, of course.
    println!(" 128 as a i16 is : {}", 128u16 as i16);
    // 128 as u8 -> 128, whose two's complement in eight bits is:
    println!(" 128 as a i8 us : {}", 128u16 as u8);
    println!(" 128 as a i8 is : {}", 128u16 as i8);
}
