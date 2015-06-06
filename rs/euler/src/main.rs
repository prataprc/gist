#![feature(zero_one)]

extern crate getopts;
extern crate time;

use getopts::Options;

use std::env;
use std::process;
use std::convert::AsRef;
use std::ops::{Sub,Add,Rem};
use std::num::{Zero};

static CHAR2DIGIT: [i64; 256] = [
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
];

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
            solve("p7", p7);
            solve("p8", p8);
            solve("p9", p9);
        },
        "p1" => solve("p1", p1),
        "p2" => solve("p2", p2),
        "p3" => solve("p3", p3),
        "p4" => solve("p4", p4),
        "p5" => solve("p5", p5),
        "p6" => solve("p6", p6),
        "p7" => solve("p7", p7),
        "p8" => solve("p8", p8),
        "p9" => solve("p9", p9),
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

fn p7() {
    let mut primes: Vec<i64> = vec![2,3,5,7,11,13,17,19];
    let mut candidate = 20;
    while primes.len() < 10001 {
        let till: i64 = ((candidate as f64).sqrt() as i64) + 1;
        let is_prime = {
            primes.iter()
                .take_while(|&p| *p < till)
                .skip_while(|&p| candidate % *p != 0 ).next().is_none()
        };
        if is_prime { primes.push(candidate) }
        candidate += 1;
    }
    println!("{:?}", &primes[10000]);
}

fn p8() {
    let inp = "73167176531330624919225119674426574742355349194934\
               96983520312774506326239578318016984801869478851843\
               85861560789112949495459501737958331952853208805511\
               12540698747158523863050715693290963295227443043557\
               66896648950445244523161731856403098711121722383113\
               62229893423380308135336276614282806444486645238749\
               30358907296290491560440772390713810515859307960866\
               70172427121883998797908792274921901699720888093776\
               65727333001053367881220235421809751254540594752243\
               52584907711670556013604839586446706324415722155397\
               53697817977846174064955149290862569321978468622482\
               83972241375657056057490261407972968652414535100474\
               82166370484403199890008895243450658541227588666881\
               16427171479924442928230863465674813919123162824586\
               17866458359124566529476545682848912883142607690042\
               84580156166097919133875499200524063689912560717606\
               05886116467109405077541002256983155200055935729725\
               71636269561882670428252483600823257530420752963450";
    let max = (0..(inp.len()-13))
        .map(|i| {
            let bytes = (&inp[i..i+13]).bytes();
            bytes.fold(1, |a, x| a * (CHAR2DIGIT[x as usize] as i64))
            // ???
            //(&inp[i..i+13]).bytes().fold(1, |a, x| a * (CHAR2DIGIT[x as usize] as i64))
        }).max().unwrap();
    println!("thirteen adjacent digits in the 1000-digit number \
             that have the greatest product: {}", max);
}

fn p9() {
    let squares: Vec<i32> = (0..1001).map(|x| x*x).collect();
    for x in squares[0..1001].iter().enumerate() {
        for y in squares[0..1001].iter().enumerate() {
            let (i, j) = ((x.0) as i32, (y.0) as i32);
            if i + j >= 1000 { break }
            let k = ((x.1 + y.1) as f64).sqrt();
            if k == k.floor() {
                let p = i * j * (k as i32);
                if (i + j + (k as i32)) == 1000  &&  p > 0 {
                    println!("pythagorean triplet's sum = 1000, product = {}",p);
                    return;
                }
            }
        }
    }
}

#[allow(dead_code)]
fn is_divisible<T>(dividend: T, divisor: T) -> bool
    where T: Rem<Output=T> + PartialEq + Zero
{
    (dividend % divisor) == T::zero()
}

#[allow(dead_code)]
fn is_triplet<T>(squares: &[T], a: usize, b: usize, c: usize) -> bool
    where T: Copy + Add<Output=T> + PartialEq
{
    (squares[a] + squares[b]) == squares[c]
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
