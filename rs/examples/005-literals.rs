// basic literals
//      integers, floats
//      boolean           true/false
//      character         ''
//      string            ""
//      unit-type         ()
fn main() {
    // integer addition
    println!("1 + 2 = {}", 1u32 + 2); // 2 is automatically coerced to u32

    // integer subraction
    println!("1 - 2 = {}", 1i32 - 2);

    // short-circuiting boolean logic
    println!("");
    println!("true AND false is {}", true && false);
    println!("true OR false is {}", true || false);
    println!("NOT true is {}", !true);

    // bitwise operations
    println!("");
    println!("0011 AND 0101 is {:04b}", 0b0011u32 & 0b0101);
    println!("0011 OR 0101 is {:04b}", 0b0011u32 | 0b0101);
    println!("0011 XOR 0101 is {:04b}", 0b0011u32 ^ 0b0101);
    println!("1 << 5 is {:x}", 1u32 << 5);
    println!("0x80(i32) >> 2 is {:x}", 0x80i32 >> 2);
    println!("0x80(i8) >> 2 is {:x}", 0x80u8 as i8 >> 2);

    // module operation
    println!("");
    println!("10(i8) % 3 is {}", 10i8 % 3);
    println!("-10(i8) % 3 is {}", 10i8 % 3);
    println!("10(i8) % -3 is {}", 10i8 % 3);
    println!("-10(i8) % -3 is {}", 10i8 % 3);
}
