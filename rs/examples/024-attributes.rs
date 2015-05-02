// An attribute of metadata applied to some module, crate
// or an item. can be used for,
//     * conditional compilation of code
//     * set crate name, version and type (binary or library)
//     * disable lints (warnings)
//     * enable compiler features (macros, glob imports, etc.)
//     * link to a foreign library
//     * mark functions as unit tests
//     * mark functions that will be part of a benchmark
//
// When attributes apply to a whole crate, their syntax is
//      #![crate_attribute]
// and when they apply to a module or item, the syntax is
//      #[item_attribute]
// Attributes can take arguments with different syntaxes:
//     #[attribute = "value"]
//     #[attribute(key = "value")]
//     #[attribute(value)]

#![crate_type="lib"] // crate is a library
#![crate_name="rary"] // and the library is names as `rary`

#[cfg(target_os="linux")]
fn are_you_on_linux() {
    println!("You are running linux!");
}

#[cfg(not(target_os="linux"))]
fn are_you_on_linux() {
    println!("You are *not* running linux!");
}

#[cfg(some_condition)] // can be supplied via $ rustc --cfg some_condition ...
fn conditional_function() {
    println!("condition met!");
}

fn mainlib() {
    are_you_on_linux();
    println!("Are you sure?");
    if cfg!(target_on="linux") {
        println!("Yes. It's definitely linux!");
    } else {
        println!("Yes. It's definitely *not* linux!");
    }
}
