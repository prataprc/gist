extern crate getopts;

use std::env;

pub fn arg_parse() -> Option<getopts::Matches> {
    let mut opts = getopts::Options::new();
    opts.parsing_style(getopts::ParsingStyle::StopAtFirstFree);

    opts.optflag("h", "help", "help listing on how to use this program");

    let args: Vec<String> = env::args().collect();
    let program = args[0].clone();
    match opts.parse(&args[1..]) {
        Ok(options) => {
            if !options.opt_present("h") {
                return Some(options)
            }
        },
        Err(f) => {
            println!("{}", f.to_string());
        }
    };
    print_usage(&program, opts);
    None
}

fn print_usage(program: &str, opts: getopts::Options) {
    let summary = format!("Usage: {} [options]", program);
    println!("{}", opts.usage(&summary));
}
