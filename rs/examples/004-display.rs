// IMPORTANT: `fmt::Display` is not implemented for Vec<T>
// or for any other generic containers.

// Import the `fmt` module to make it available via `use`.
use std::fmt;

// Define a structure which `fmt::Display` will be implemented for.
struct Structure(i32);

// In order to use `{}` marker, the trait `fmt::Display` must
// be implemented manually for the type.
impl fmt::Display for Structure {
    // this trait requires `fmt` with this exact signature.
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.0)
    }
}

fn main() {
    println!("{}", Structure(19));
}
