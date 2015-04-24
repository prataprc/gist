extern crate getopts;
use getopts::Options;
use std::env;
use std::process;

fn print_usage(program: &str, opts: Options) {
    let summary = format!("Usage: {} [options]", program);
    println!("{}", opts.usage(&summary));
}

fn argParse() -> getopts::Matches {
    let args: Vec<String> = env::args().collect();
    let program = args[0].clone();
    let mut opts = Options::new();
    opts.optflag("h", "help", "help listing on how to use this program");
    let options = match opts.parse(&args[1..]) {
        Ok(m) => { m }
        Err(f) => { panic!(f.to_string()) }
    };
    if options.opt_present("h") {
        print_usage(program.deref(), opts);
        process::exit(1);
    }
    options
}

fn main() {
    let options = argParse();
    match options.free[0].as_str() {
        "p1" => { p1() }
        _ => process::exit(2)
    };
}

fn p1() {
    let mut sum = 0;
    for i in 0..1000 {
        if (i % 3) == 0 && (i % 5) == 0 {
            sum += i
        }
    }
    println!("the sum of all the multiples of 3 or 5 below 1000: {} \n", sum);
}
