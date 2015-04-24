fn main() {
    let _immutable_binding = 1; // by default a variable-binding is immutable.
    let mut mutable_binding = 1;

    println!("before mutation: {}", mutable_binding);
    mutable_binding += 2;
    println!("after mutation: {}", mutable_binding);

    _immutable_binding = 2; // FIXME is an error.
}
