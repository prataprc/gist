#[derive(Debug)]
struct MyT {
    a: i32,
}
#[derive(Debug)]
struct X {
    a: MyT,
    b: MyT,
}

fn main() {
    // x is partially moved.
    let x = X{a: MyT{a:200}, b: MyT{a:300}};
    let a = x.a;
    let b = x.b;
    println!("moved struct fields {:?} {:?}", a, b);

    // x is partially moved with mutability
    let mut x = X{a: MyT{a:200}, b: MyT{a:300}};
    let a = &mut x.a;
    let b = &mut x.b;
    println!("moved struct fields {:?} {:?}", a, b);
    a.a = 10;
    b.a = 20;
    println!("moved struct fields {:?} {:?}", a, b);

    // x is partially moved with mutability with scope.
    let mut x = X{a: MyT{a:200}, b: MyT{a:300}};
    {
        let a = &mut x.a;
        let b = &mut x.b;
        a.a = 10;
        b.a = 20;
    }
    println!("moved struct fields {:?}", x);

    // cannot partially move fields on borrowed struct.
    let x = &X{a: MyT{a:200}, b: MyT{a:300}};
    let a = x.a;
    let b = x.b;
    println!("moved struct fields {:?} {:?}", a, b);
}
