// `Debug` implementation are available only for types in std library.
// Other times can implement the `Debug` themself or it can derive
// the fmt::Debug implementation.

// cannot be printed either with `fmt::Debug` or with `fmt::Display`.
struct Unprintable(i32);

// The derive attribute automatically creates the implementation
// required to make this `struct` printable with fmt::Debug
#[derive(Debug)]
struct DebugPrintable(i32);

// A deep structure.
#[derive(Debug)]
struct Deep(DebugPrintable);

fn main() {
    println!("{:?} months in a year", 12);
    println!("{1:?} {0:?} is the {actor:?} name.",
             "Slater",
             "Christian",
             actor="actor's");
    // `Structure` is printable!
    println!("Now {:?} will print!", DebugPrintable(3));

    // The problem with `derive` is there is no control over how
    // the results look. What if I want this to just show a `7`?
    println!("Now {:?} will print!", Deep(DebugPrintable(7)));
}
