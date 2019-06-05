use std::{
    fs, io,
    io::{Seek, Write},
    path,
};

fn main() {
    let mut dir = std::env::temp_dir();
    dir.push("test_file.txt");
    let file = dir.as_path().to_str().unwrap();

    let p = path::Path::new(file);
    let mut opts = fs::OpenOptions::new();
    let parent = p.parent().unwrap();
    fs::create_dir_all(parent).ok();
    fs::remove_file(p).ok();
    let mut fd = opts.append(true).create_new(true).open(p).unwrap();

    fd.write("hello world".as_bytes()).expect("write failed");
    fd.seek(io::SeekFrom::Start(1)).expect("seek failed");
    fd.write("i world".as_bytes()).expect("write failed");

    let txt = fs::read(file).expect("read failed");
    assert_eq!(std::str::from_utf8(&txt).unwrap(), "hello worldi world");
}
