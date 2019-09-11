use std::mem;

struct Foo;

fn main() {
    let v = vec![10, 20, 30, 40, 50, 60];

    println!(
        "size of i8/{}, u8/{}, i16/{}, u16/{}, i32/{}, u32/{}, i64/{}, u64/{}",
        mem::size_of::<i8>(),
        mem::size_of::<u8>(),
        mem::size_of::<i16>(),
        mem::size_of::<u16>(),
        mem::size_of::<i32>(),
        mem::size_of::<u32>(),
        mem::size_of::<i64>(),
        mem::size_of::<u64>()
    );
    println!(
        "size of &i8/{}, &u8/{}, &i64/{}, &u64/{}, &bool/{}",
        mem::size_of::<&i8>(),
        mem::size_of::<&u8>(),
        mem::size_of::<&i64>(),
        mem::size_of::<&u64>(),
        mem::size_of::<&bool>()
    );
    println!(
        "size of isize/{}, usize/{}",
        mem::size_of::<isize>(),
        mem::size_of::<usize>()
    );
    println!("size of bool/{}", mem::size_of::<bool>());
    println!("size of ()/{}", mem::size_of::<()>());
    println!("size of `struct Foo`/{}", mem::size_of::<Foo>());
    println!("size of `Box::new(5: u32)`/{}", mem::size_of::<Box<u32>>());
    println!("size of `Box::new(5: u8)`/{}", mem::size_of::<Box<u8>>());
    println!("size of Option<()>/{}", mem::size_of::<Option<()>>());
    println!("size of Option<u16>/{}", mem::size_of::<Option<u16>>());
    println!("size of Option<u64>/{}", mem::size_of::<Option<u64>>());
    println!("size of Option<u64>/{}", mem::size_of::<Option<u64>>());
    println!("size of vector {}", mem::size_of_val(&v));
}
