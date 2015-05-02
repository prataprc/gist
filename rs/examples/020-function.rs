// Unlike C/C++ there is no restriction on the order of function definitions
fn main() {
    // we can use this function here and define it somewhere later
    fizzbuzz_to(100);

    used_function(); // demonstrate dead_code lint
}

// functions are declared using the `fn` keyword. Its arguments are
// type annotated, just like variables, and, if the function returns
// a value, the return type must be specified after an array `->`.
fn is_divisible_by(lhs: u32, rhs: u32) -> bool {
    // corner case, early return
    if rhs == 0 {
        return false; // return can be used for explicit return
    }
    lhs % rhs == 0 // last expresion (without ; suffix) is returned
}

// functions that don't return a value, actually return the unit-type
fn fizzbuzz(n: u32) -> () {
    // the return type of the `if` expression is unit-type.
    if is_divisible_by(n, 15) {
        println!("fizzbuzz"); // last expression with ; suffix return unit-type
    } else if is_divisible_by(n, 3) {
        println!("fizz");
    } else if is_divisible_by(n, 5) {
        println!("buzz");
    } else {
        println!("{}", n);
    }
}

// when a function returns `()`, the return type can be omitted from the
// signature.
fn fizzbuzz_to(n: u32) {
    for n in 1..n + 1 {
        fizzbuzz(n);
    }
}

// dead_code lint
fn used_function() {}

// disables the dead_code lint
#[allow(dead_code)]
fn unused_function() {}
