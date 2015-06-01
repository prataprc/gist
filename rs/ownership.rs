#[derive(Debug)]
struct Person {
    first: String,
    last: String
}

#[derive(Debug)]
struct Foo(i32, i8);

#[derive(Debug,Clone,Copy)]
struct Bar(i32, i8);

#[derive(Debug)]
enum MyEnum {
    X(i32),
    Y(Box<i32>)
}

#[allow(unused_variables,unused_mut)]
fn main() {
    // what is ownership
    {
        let yehuda = Person {first: "Yehuda".to_string(), last: "Katz".to_string()};
        // `yehuda` ownership is transferred to `name_size`, so it cannot be
        // used anymore in this scope, and it will not be destroyed
        // when this scope exits. It is up to `name_size`,
        // or possibly a future owner, to destroy it.
        let size = name_size(yehuda);

        let tom = Person {first: "Tom".to_string(), last: "Dale".to_string()};
        // `tom` wasn't transferred, so it will be
        // destroyed when this scope exits.
        println!("size of yehuda {}, tom {:?}", size, tom);
    }

    // what is transfer of ownership
    {
        let x = Foo(10, 20); // x has immmutable ownership of Foo(10,20);
        let y = x; // x is _moved_ to y. y has immutable ownership of Foo(10,20);
        println!("transferred ownership to y {:?}", y); // so you can use y
        // println!("{:?}", x); <- FAIL: but cannot use moved x.
    }

    // what is copy semantics (create new owners, as opposed to transfer/move)
    {
        let x = Bar(10, 20); // x has immmutable ownership of Bar(10, 20)
        let y = x; // x is copied to y. another owner is created.
        // now you can use both x and y.
        println!("owner 1: {:?} owner 2: {:?}", x, y);
    }

    // what is borrow,
    // one-immutable owner and 0-N immutable borrows (references &T).
    {
        let x = Foo(10, 20);
        let y = &x;
        let z = &x;
        println!("owner: {:?} borrow-1: {:?} borrow-2: {:?}", x, y, z);
    }

    // what is borrow,
    // one-mutable owner and 0-N immutable borrows.
    {
        let mut x = Foo(10, 20);
        x.0 = 30;
        let y = &x;
        let z = &x;
        println!("owner: {:?} immut-borrow-1: {:?} immut-borrow-2: {:?}", x, y, z);
        // prints: owner: Foo(30, 20) borrow-1: Foo(30, 20) borrow-2: Foo(30, 20)
    }

    // what is borrow,
    // cannot assign to `x.0` because it is borrowed
    {
        let mut x = Foo(10, 20);
        let y = &x;
        // x.0 = 30; <- FAIL: not allowed
    }

    // what is borrow,
    // cannot borrow `x` as immutable because it is also borrowed as mutable
    {
        let mut x = Foo(10, 20);
        let y = &mut x;
        // println!("owner: {:?} borrow-1: {:?}", x, y); <- FAIL:
    }

    // what is borrow,
    // cannot borrow `x` as mutable more than once at a time
    {
        let mut x = Foo(10, 20);
        let y = &mut x;
        // let z = &mut x; <- FAIL: not allowed
    }

    let x = MyEnum::X(3);
    match_and_print_own(x); // ownership passed to the function.
    // println!("variant X {:?}", x); <- FAIL: not allowed

    let y = MyEnum::Y(Box::new(4));
    match_and_print_own(y); // callee is owner `y`
    // println!("variant Y {:?}", y); <- FAIL not allowed

    let x = MyEnum::X(3);
    match_and_print_borrow(&x); // function borrows `x`
    println!("variant X {:?}", x);

    let y = MyEnum::Y(Box::new(4));
    match_and_print_borrow(&y); // function borrows `y`
    println!("variant Y {:?}", y);
}

fn match_and_print_own(e: MyEnum) {
    // move semantics or copy semantics can only be done when we have
    // ownership over the values to be moved.
    match e { // match will move/copy `e` over to matching arm.
        MyEnum::X(x) => println!("variant X {}", x),
        MyEnum::Y(y) => println!("variant Y {}", y)
    }
}

fn match_and_print_borrow(e: &MyEnum) {
    match e {
        &MyEnum::X(x) => println!("variant X {}", x),

        // cannot move out of borrowed content
        // &MyEnum::Y(y) => println!("variant Y {}", y)

        // `ref` keyword comes into play: It changes the pass-by-value
        // semantics of a pattern match to pass-by-borrowed-pointer semantics.
        &MyEnum::Y(ref y) =>
            {
                let f = e;
                println!("variant Y {}", y);
                println!("moved e {:?} to f {:?}", e, f)
            }
    }
}

fn name_size(person: Person) -> usize {
    let Person { first, last } = person;
    first.len() + last.len()
    // this function owns Person, so the Person is destroyed when `name_size` returns
}
