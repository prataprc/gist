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
            solve("p5", p5);
            solve("p6", p6);
        },
        "p1" => solve("p1", p1),
        "p2" => solve("p2", p2),
        "p3" => solve("p3", p3),
        "p4" => solve("p4", p4),
        "p5" => solve("p5", p5),
        "p6" => solve("p6", p6),
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
    //let max = prime_factors(600851475143_i64)
    //    .iter()
    //    .fold(0, |max, n| if (n > max) {n} else {max});
    println!("largest prime factor of the number 600851475143: {:?}", 10);
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

fn p5() {
    let primes = vec![2,3,5,7,11,13,17,19];
    let mut result = primes.iter().fold(1, |a, x| a * x);
    for x in vec![4,6,8,10,12,14,15,16,18,20] {
        let mut val = result;
        for p in prime_factors(x) {
            if (val % p) == 0 { val /= p } else { result *= p }
        }
    }
    println!("smallest positive number that is evenly divisible \
             by all of the numbers from 1 to 20 {}", result);
}

fn p6() {
    let s1 = (1..101).map(|x| x*x).fold(0, |a, x| a+x);
    let s2 = (1..101).fold(0, |a, x| a+x);
    println!("difference between the sum of the squares of the first \
              one hundred natural numbers and the square of the sum: {}", (s2*s2)-s1);
}

fn is_palindrome<T: Eq>(x: &[T]) -> bool {
    let i = x.len()/2;
    (&x[..i]).iter().zip((&x[i..]).iter().rev()).all(|(a,b)| a == b)
}

fn prime_factors(num: i64) -> Vec<i64> {
    let mut number = num;
    let mut pfactors = Vec::new();
    let mut candidate = 2;
    while number > 1 {
        while number % candidate == 0 {
            pfactors.push(candidate);
            number /= candidate;
        }
        candidate += 1;
    }
    return pfactors;
}

#[allow(dead_code)]
fn is_prime(num: i64) -> bool {
    let till: i64 = ((num as f64).sqrt() as i64) + 1;
    let mut fs = Vec::new();
    (2..till).fold(true, |_, i| {if (num % i) == 0 {fs.push(i)}; true});
    fs.len() == 0
}

#[allow(dead_code)]
fn factors_cb<F>(num: i64, mut f: F) where F: FnMut(i64) {
    let till: i64 = ((num as f64).sqrt() as i64) + 1;
    for i in 2..till {
        if (num % i) == 0 {
            f(i);
            factors_cb(num / i, f);
            return
        }
    }
    f(num);
}
