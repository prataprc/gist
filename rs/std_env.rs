use std::env;

fn main() {
    let mut args = env::args();
    if let Some(arg0) = args.next() {
        println!("{}", arg0);
        let x: String = arg0;
        println!("{}", x);
        println!("{:?}", args);
    }
}
