#![allow(unused)]
fn main() {
    use std::path::{Path, PathBuf};

    let path = Path::new("../rs/canonicalize.rs");
    println!("{:?}", path.canonicalize().unwrap());

    let path = Path::new("mods/okay.rs");
    println!("{:?}", path.canonicalize().unwrap());
}
