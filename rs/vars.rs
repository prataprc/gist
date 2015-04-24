fn main() {
    let an_integer = 1u32;
    let a_boolean = true;
    let unit = ();

    let copied_int = an_integer;
    println!("An integer: {:?}", copied_int);
    println!("A boolean: {:?}", a_boolean);
    println!("Meet the unit value: {:?}", unit);

    // suppress compiler warning on unused variable by prefixing with `_`.
    let _unused_variable = 3u32;

    mutability();
    declare_first();
}

fn mutability() {
    let _immutable_int = 1;
    let mut mutable_int = _immutable_int;

    println!("Before mutation: {}", mutable_int);

    mutable_int += 1;

    println!("After mutation: {}", mutable_int);

    // the following is a compiler error
    // _immutable_int += 1
}

fn declare_first() {
    let default_var;
    default_var = true;
    println!("default_var {}", default_var);
}

fn _unused_fn() {
    println!("i am not used")
}
