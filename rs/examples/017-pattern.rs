// pattern-matching

#[allow(unused_variables)]
fn main() {
    println!("match-pattern");
    println!("-------------");
    match_pattern();

    println!("tuple-deconstruct");
    println!("-----------------");
    tuple_deconstruct();

    println!("enum-sum-types");
    println!("--------------");
    enum_sum_types();

    println!("pointer-ref");
    println!("-----------");
    pointer_ref();

    println!("struct_match");
    println!("------------");
    struct_match();

    println!("guard-match");
    println!("-----------");
    guard_match();

    println!("match-binding");
    println!("-------------");
    match_binding();
}

fn match_pattern() {
    let number = 13;
    println!("tell me about {}", number);
    match number {
        1 => println!("one!"), // match a single value
        2 | 3 | 5 => println!("this is a prime"), // match several values
        n @ 13...19 => println!("a teen {:?}", n), // match an inclusive range.
        _ => println!("Ain't special"), // catch all case.
    }

    let boolean = true;

    let binary = match boolean { false => 0, true => 1 };
    println!("{} -> {}", boolean, binary);
}

fn tuple_deconstruct() {
    // tuples can be destructured in a match as follows
    let pair = (0, -1); // (i32, i32)

    println!("Tell me aboutn {:?}", pair);

    // match can be used to destructure a tuple
    match pair {
        (0, y) => println!("First is `0` and `y` is {:?}", y),
        (x, 0) => println!("x is {:?} and last is 0", x),
        _      => println!("It doesn't matter what they are")
    }

    let (x, y) = pair;
    println!("can be destructured while assignment ({:?}, {:?})", x, y);

    // (x, y) = (10, 20);
    // println!("can be destructured without let as well ({:?}, {:?})", x, y);
}

#[allow(dead_code)] // silence warnings because `Color` is never used.
#[derive(Debug)]
enum Color {
    // There 3 are specified solely by their name.
    Red,
    Blue,
    Green,
    // This requires 3 `i32`s and a name.
    RGB(i32, i32, i32),
}

fn enum_sum_types() {
    let color = Color::RGB(122, 17, 40);

    println!("What color is it?");
    match color {
        Color::Red => println!("The color is Red!"),
        Color::Blue => println!("The color is Blue!"),
        Color::Green => println!("The color is Green!"),
        Color::RGB(r,g,b) => println!("Red {:?} Green {:?} Blue {:?}", r, g, b),
    }
}

fn pointer_ref() {
    // Assign a reference of type `i32`. The `&` signifies there
    // is reference being assigned.
    let reference = &4;

    match reference {
        // If `reference` is pattern matched against `&val`, it
        // results in a comparision like `&i32` or `&val`.
        // we see that if matching `&` is dropped, then the `i32`
        // should be assigned to `val`.
        &val => println!("Got a value via destructuring: {:?}", val)
    }
    // To avoid the `&`, you deference before matching.
    match *reference {
        val => println!("Got a value via dereferencing: {:?}", val),
    }
    // what if you don't start with a reference ?
    let _not_a_reference = 3;
    let ref _is_a_reference = 3; // `ref` can be used in such cases.

    // Accordingly by defining 2 values without references, references
    // can be retrieved via `ref` and `ref mut`
    let value = 5;
    let mut mut_value = 5;

    // Use `ref` keyword to create a reference.
    match value {
        ref r => println!("Got a reference to value: {:?}", r),
    }

    // use `ref mut` similarly.
    match mut_value {
        ref mut m => {
            // got a reference. gotta dereference it befor we can
            // add anything to it.
            *m += 10;
            println!("we added 10. `mut_value`: {:?}", m);
        },
    }
}

fn struct_match() {
    struct Foo {x: (u32, u32), y: u32}

    // destructure members of struct.
    let foo = Foo{x : (1,2), y: 3};
    let Foo{x: (a, b), y} = foo;

    println!("a = {}, b= {}, y = {}", a, b, y);

    // you can destruture structs and rename the variables,
    // the order is not important.
    let Foo{y: i, x: j} = foo;
    println!("i = {:?}, j = {:?}", i, j);

    // and you can also ignore some variables
    let Foo{y, ..} = foo;
    println!("y = {}", y);
}

fn guard_match() {
    // a match gaurd can be added to filter the arm.
    let pair = (2, -2);

    println!("Tell me about {:?}", pair);
    match pair {
        (x, y) if x == y => println!("These are twins"),
        (x, y) if x + y == 0 => println!("Antimatter, kaboom!"),
        (x, _) if x % 2 == 1 => println!("The first one is odd"),
        _ => println!("catch all..")
    }
}

fn match_binding() {
    // indirectly accessing a variable makes it impossible to
    // branch and use that variable without re-binding.
    // use `@` sigil
    let f = || { 12 };
    match f() {
        0 => println!("I'm not born yet I guess"),
        // could `match` 1 ... 12 directly but then what age
        // would the child be ? Instead, bind to `n` for the
        // sequence of 1 .. 12. Now the age can be reported.
        n @ 1 ... 11 => println!("I'm a child of age {}", n),
        n @ 12 ... 18 => println!("I'm a teen of age {}", n),
        n => println!("I'm an old person of age {}", n),
    }
}
