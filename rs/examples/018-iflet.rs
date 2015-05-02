fn main() {
    // All have type `Option<i32>`
    let number = Some(7);
    let letter: Option<i32> = None;

    // The `if let` construct reads: "if `let` destructures `number` into
    // `Some(i)`, evaluate the block (`{}`). Else do nothing.
    if let Some(i) = number {
        println!("Matched {:?}", i);
    }

    // If you need to specify a failure, use an else:
    if let Some(i) = letter {
        println!("Matched {:?}", i);
    } else {
        println!("Didn't match a number. Let's go with a letter!");
    };
}
