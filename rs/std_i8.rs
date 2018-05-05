#![feature(iterator_step_by)]

fn main() {
    let n = 0b1000_0000i8;

    println!("{} {}", i8::min_value(), i8::max_value());
    assert_eq!(i8::from_str_radix("A", 16), Ok(10));

    println!(
        "{} {} {} {}", n.count_ones(), n.count_zeros(),
        n.leading_zeros(), n.trailing_zeros(),
    ); // o: 1 7 0 7

    println!("{}", i8::from_be(10));
}

fn bit_rotation() {
    println!("\nbit rotation :");
    let num: i8 = 0x12;
    for x in (4..9).step_by(4) {
        println!("i8 {} {:x}", x, num.rotate_left(x));
    }
    let num: i64 = 0x0123456789abcdef;
    for x in (4..65).step_by(4) {
        let out = num.rotate_left(x);
        println!("i64 {} {:x} {}", x, out, out);
    }
    let num: i64 = 0x0123456789abcdef;
    for x in (4..65).step_by(4) {
        let out = num.rotate_right(x);
        println!("i64 {} {:x} {}", x, out, out);
    }
}

fn swap_bytes() {
    let n: i16 = 0b0000000_01010101;
    assert_eq!(n.swap_bytes(), 0x5500);
    let n: i32 = 0x12345678;
    println!("i32 {:x} {:x}", n, n.swap_bytes());
}

fn checked_neg() {
    println!("checked_neg() {:?}", 127i8.checked_neg());
    println!("checked_neg() {:?}", (-127i8).checked_neg());
    println!("checked_neg() {:?}", (-128i8).checked_neg());
}
