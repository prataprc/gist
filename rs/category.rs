fn identity<T>(a: T) -> T { a }
fn compose<'a,A,B,C>(a: &Fn(B)->C, b: &Fn(A)->B) -> &'static (Fn(A) -> C) {|x: A| {a(b(x))}}

fn main() {
    let a = 10;
    println!("identity of T {:?}", identity(a));
    println!("identity of &T {:?}", identity(&a));

    let f = |x: u8| {x as u16 };
    let g = |x: u16| {x as u32 };
    println!("compose {:?}", compose(f,g));
}
