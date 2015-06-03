extern crate getopts;
extern crate time;

use getopts::Options;

use std::env;
use std::process;
use std::convert::AsRef;
use std::ops::Sub;

fn print_usage(program: &str, opts: Options) {
    let summary = format!("Usage: {} [options]", program);
    println!("{}", opts.usage(&summary));
}

fn arg_parse() -> getopts::Matches {
    let mut opts = Options::new();
    opts.optflag("h", "help", "help listing on how to use this program");

    let args: Vec<String> = env::args().collect();
    let program = args[0].clone();

    let options = match opts.parse(&args[1..]) {
        Ok(m) => { m },
        Err(f) => { panic!(f.to_string()) },
    };
    if options.opt_present("h") {
        print_usage(&program, opts);
        process::exit(1);
    };
    options
}

fn main() {
    let options = arg_parse();
    if options.free.len() < 1 {
        println!("supply problem number !!");
        process::exit(1);
    };
    match options.free[0].as_ref() {
        "all" => {
            solve("p1", p1);
            solve("p1", p1);
            solve("p2", p2);
            solve("p3", p3);
            solve("p4", p4);
        },
        "p1" => solve("p1", p1),
        "p2" => solve("p2", p2),
        "p3" => solve("p3", p3),
        "p4" => solve("p4", p4),
        _ => {println!("supply problem number !!"); process::exit(2);},
    };
}

fn solve(prob_name: &str, solver: fn()) {
    let start = time::now();
    solver();
    println!("\"{}\" took {}\n", prob_name, time::now().sub(start));
}

fn p1() {
    let mut sum = 0_u32;
    for i in 0..1000 {
        if (i % 3) == 0 || (i % 5) == 0 {
            sum += i
        }
    };
    println!("the sum of all the multiples of 3 or 5 below 1000: {}", sum);
}

fn p2() {
    let till: u64 = 4 * 1000 * 1000;
    let mut ab: (u64, u64) = (1, 2);
    let mut sum = ab.0;
    while ab.1 < till {
        sum += ab.1;
        ab = (ab.1, ab.0+ab.1)
    }
    println!("sum of even-valued terms in the fibonacci sequence 1,2...");
    println!("   whose values do not exceed four million: {}", sum);
}

fn p3() {
    let mut max = 0_i64;
    { let f = |n: i64| if n > max { max = n };
      factors(600851475143_i64, f);
    }
    println!("largest prime factor of the number 600851475143: {}", max);
}

fn p4() {
    let mut result: u64 = 0;
    for i in (99..1000).rev() {
        for j in (i..1000).rev() {
            let num = i * j;
            if is_palindrome(num.to_string().as_bytes()) {
                if result < num {
                    result = num;
                }
            }
        }
    }
    println!("largest palindrome made from the product of two 3-digit numbers {}", result);
}

fn is_palindrome<T: Eq>(x: &[T]) -> bool {
    let i = x.len()/2;
    (&x[..i]).iter().zip((&x[i..]).iter().rev()).all(|(a,b)| a == b)
}

fn factors<F>(num: i64, mut f: F) where F: FnMut(i64) {
    let till: i64 = ((num as f64).sqrt() as i64) + 1;
    for i in 2..till {
        if (num % i) == 0 {
            f(i);
            factors(num / i, f);
            return
        }
    }
    f(num);
}