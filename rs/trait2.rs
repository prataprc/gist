trait MyTraitConsume {
    fn consume(self);
}

trait MyTraitBorrow {
    fn borrow(&self);
}

trait MyTraitMutable {
    fn mutable(&mut self);
}

struct MyType{a: i32}

impl MyTraitConsume for MyType {
    fn consume(self) {
        println!("consumed");
    }
}

impl MyTraitBorrow for MyType {
    fn borrow(&self) {
        println!("borrowed");
    }
}

impl MyTraitMutable for MyType {
    fn mutable(&mut self) {
        println!("borrowed");
    }
}

impl<'a> MyTraitConsume for &'a MyType {
    fn consume(self) {
        println!("consumed");
    }
}

impl<'a> MyTraitBorrow for &'a MyType {
    fn borrow(&self) {
        println!("borrowed");
    }
}

impl<'a> MyTraitMutable for &'a MyType {
    fn mutable(&mut self) {
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
