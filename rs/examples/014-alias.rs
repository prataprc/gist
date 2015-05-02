// the type statement can be used to give a new name to an existing
// type.  use CamelCase.  but primitive types can be small cases.

// `NanoSecond` is a new name for u64.
type NanoSecond = u64;
type Inch = u64;

// use an attribute to silence warning.
#[allow(non_camel_case_types)]
type  u64_t = u64;

// use an attribute to silence warnings;
#[allow(trivial_numeric_casts)]
fn main() {
    let ns: NanoSecond = 5 as u64_t;
    let inches: Inch = 2 as u64;

    // Note that type aliases *don't* provide any extra type safety,
    // because aliases are *not* new types.
    println!("{} nanoseconds + {} inches = {} uint?",
             ns,
             inches,
             ns + inches)
}
