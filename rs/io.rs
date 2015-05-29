use std::io;

fn main() {
    let ref mut stdin: io::Stdin = io::stdin();
    read_line(stdin);
}

fn read_line(stdin: &mut io::Stdin) {
    let ref mut s = String::new();
    let res = stdin.read_line(s);
    println!("res: {:?}", res);
    println!("input recieved {:?}", s);
}

//fn read_trait(stdin &mut io::Stdin) {
//}
