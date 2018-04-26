#![feature(zero_one)]

extern crate getopts;
extern crate euler;

mod args;

use std::process;
use std::ops::{Add,Rem};
use std::default::{Default};
use std::time::{SystemTime};

fn main() {
    let options = args::arg_parse();
    if options.is_none() {
        process::exit(1);
    }
    let options = options.unwrap();

    for freearg in options.free.as_slice().iter() {
        solve(freearg);
    }
}

fn solve(arg: &str) {
    let total = euler::solutions.len()+1;

    match usize::from_str_radix(arg, 10) {
        Err(err) =>
            println!("invalid problem number: {} ({}) ", arg, err),
        Ok(num) if num >= total =>
            println!("invalid problem number: {} must be < {}", num, total),
        Ok(num) => {
            let start = SystemTime::now();
            let solver = euler::solutions[num];
            solver();
            println!("\"{}\" took {:?}\n", arg, start.elapsed().unwrap());
        },
    }
}

#[allow(dead_code)]
fn is_divisible<T>(dividend: T, divisor: T) -> bool
    where T: Rem<Output=T> + PartialEq + Default
{
    (dividend % divisor) == Default::default()
}

#[allow(dead_code)]
fn is_triplet<T>(squares: &[T], a: usize, b: usize, c: usize) -> bool
    where T: Copy + Add<Output=T> + PartialEq
{
    (squares[a] + squares[b]) == squares[c]
}

#[allow(dead_code)]
fn is_palindrome<T: Eq>(x: &[T]) -> bool {
    let i = x.len()/2;
    (&x[..i]).iter().zip((&x[i..]).iter().rev()).all(|(a,b)| a == b)
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
