// all variables have a scope, and are constrained to live in
// a block.

fn main() {
    let long_lived_binding = 1;

    // nested BLOCK, say we call it A
    {
        let short_lived_binding = 2; // restricted to block A.
        println!("inner short: {}", short_lived_binding);

        let long_lived_binding = 3.1; // shadow binding, note different types
        println!("inner long: {}", long_lived_binding);
    }

    println!("outer long: {}", long_lived_binding);
}
