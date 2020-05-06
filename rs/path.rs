fn main() {
    use std::path::{Path, PathBuf};
    let path = Path::new("~/myworld/devgit/gist/rs/path.rs");
    println!("{:?}", path.canonicalize());
}
