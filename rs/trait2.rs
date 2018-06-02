trait MyTrait {
    fn consume(self);
    fn borrow(&self);
}

struct MyType{a: i32}

impl MyTrait for MyType {
    fn consume(self) {
        println!("consumed");
    }
    fn borrow(&self) {
        println!("borrowed");
    }
}

impl<'a> MyTrait for &'a MyType {
    fn consume(self) {
        println!("consumed");
    }
    fn borrow(&self) {
        println!("borrowed");
    }
}

fn main() {
    let t = MyType{a:10};
    t.consume();
    // println!("{}", t.a); <-- use of moved value.

    let t = MyType{a:10};
    t.borrow();
    println!("{}", t.a); // <-- borrow returned,

    let t = &MyType{a:10};
    t.consume();
    println!("{}", t.a);
}
