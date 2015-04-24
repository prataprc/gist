// it is possible to declar variable binding first, and
// initialize them later. however, it may lead to the use
// of un-initialzed variables.

fn main() {
    // declare a variable binding
    let a_binding;
    {
        let x =2;
        // initialize the binding;
        a_binding = x * x;
    }
    println!("a binding: {}", a_binding);

    let another_binding;
    // FIXME: use of uninitialized binding.
    //println!("another binding: {}", another_binding);
    another_binding = 1;
    println!("another binding: {}", another_binding);
    println!("a binding: {}", a_binding);
}
