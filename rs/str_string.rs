use std::path::{PathBuf};

fn main() {
    let mut ownp = PathBuf::new();
    ownp.push("/tmp");
    let refp = ownp.as_path();
    println!("{:?}", refp);
    ownp.push("b");
}
