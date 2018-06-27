use std::fs::{self,Permissions};

impl Permissions {
    fn ok() -> bool { true }
}

fn main() {
    let perms = fs::metadata("/").unwrap().permissions();
    println!("{}", perms.ok());
}
