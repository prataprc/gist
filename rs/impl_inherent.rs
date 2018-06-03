#[derive(Debug)]
struct Y { a: i32 }
struct X { y: Y }

// this is not possible "no base type found for inherent implementation"
//impl<'a> &'a X {
//    fn borrow(self) -> &'a i32 {
//        self.a
//    }
//}

impl X {
    fn borrow(&self) -> &Y {
        &self.y
    }
}

fn main() {
    let x = X{y:Y{a:10}};
    let y = x.borrow();
    println!("{:?}", y);
}

