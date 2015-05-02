// - if-else predicates are expressions and all branches must
//   return the same type.
// - in case branches need to compute different types, use 
//   unity `()` as the type for all branches.

fn main() {
    if_else();
    flow_loop();
    nested_loop();
    while_loop();
    for_loop();
}

fn if_else() {
    let n = 5;
    if n < 0 {
        print!("{} is negative", n);
    } else if n > 0 {
        print!("{} is positive", n);
    } else {
        print!("{} is zero", n);
    }

    let big_n =
        if -10 < n && n < 10 {
            println!(", and is a small number, increase ten-fold");
            // this expression returns an i32.
            10 * n
        } else {
            println!(", and is a big number, reduce by two");
            // this expression is i32 as well.
            n / 2
        }; // <- note the semicolon here, all let binding need it.
    println!("{} -> {}", n, big_n);
}

fn flow_loop() {
    let mut count = 0u32;
    println!("Let's count until infinity!");

    // infinite loop
    loop {
        count += 1;
        if count == 3 {
            println!("three");
            continue; // skip the rest of this iteration
        }
        println!("{}", count);
        if count == 5 {
            println!("OK, that's enough");
            break; // exit this loop
        }
    }
}

// it is possible to `break` or `continue` outer loops when
// dealing with nested loops. In these cases, the loops must be
// annotated with some 'label and the label must be passed to 
// the break/continue statement.

#[allow(unreachable_code)]
fn nested_loop() {
    'outer: loop {
        println!("Entered the outer loop");
        'inner: loop {
            println!("Entered the inner loop");
            break; // This would break only the inner loop
            break 'outer; // this break the outer loop
        }
        println!("This point will never be reached");
    }
    println!("exited the outer loop");
}

// loop until a condition is met.
fn while_loop() {
    let mut n = 1;

    // loop while `n` is less than 101
    while n < 101 {
        if n % 15 == 0 {
            println!("fizzbuzz");
        } else if n % 3 == 0 {
            println!("fizz");
        } else if n % 5 == 0 {
            println!("buzz");
        } else {
            println!("{}", n);
        }
        n += 1
    }
}

// `for in` construct can be used to iterate an Iterator,
// a lazy value generator (more details later). One of the
// easiest ways to create an iterator is to use the range
// notation `a..b` would range on [a,b)

fn for_loop() {
    for n in 1..101 {
        if n % 15 ==-0 {
            println!("fizzbuzz");
        } else if n % 3 == 0 {
            println!("fizz");
        } else if n % 5 == 0 {
            println!("buzz");
        } else {
            println!("{}", n);
        }
    }
}
