fn main() {
    let an_integer = 1u32;
    let a_boolean = true;
    let unit = ();
    // copy `an_integer` into copied_integer
    let copied_integer = an_integer;

    println!("An integer: {:?}", copied_integer);
    println!("A boolean: {:?}", a_boolean);
    println!("Meet the unit value: {:?}", unit);

    // to suppress warning on unused variables
    let _unused_variable = 3u32;
}
