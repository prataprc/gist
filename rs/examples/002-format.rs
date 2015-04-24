// printing is handled by a series of macros defined in std::fmt,
// some of which include,
//      format!
//      print!
//      println!
//      write!
//
// std::fmt contains several traits that convern the display of data as text.
//      fmt.Debug    uses {:?}
//      fmt.Display  uses {}

fn main() {
    // in general, the {} will be automatically replaced with any
    // argument. These will be stringified.
    println!("{} days", 31); // without suffix, 31 is treated as type i32.
    println!("{} days", 31u64); // now with u64 suffix 31 is treated as type u64.

    // positional arguments.
    println!("{0}, this is {1}. {1}, this is {0}", "Alice", "Bob");

    // named arguments.
    println!("{subject} {verb} {predicate}",
             predicate="over the lazy log",
             subject="the quick brown fox",
             verb="jumps");

    // special formatting can be specified after a `:`
    println!("{} of {:b} people know binary, the other half don't", 1, 2);

    // create a structure which contains an i32.
    struct _Structure(i32); // prefixing with `_` will supress unused warning.

    // Structure does not implement the Display trait.
    //FIXME println!("{}", Structure(2));
}
