fn main() {
    let mut x = &4;
    println!("x {:p}", x);
    match x {
         &mut ref mut v => {*v = 10; println!("v {:p} {:?}", v, v)},
    }
}
