use primes;

// 2520 is the smallest number that can be divided by each of the numbers
// from 1 to 10 without any remainder.
// What is the smallest positive number that is evenly divisible by all
// of the numbers from 1 to 20?
pub fn solve() {
    let primes: Vec<u32> = primes::Primes::new(20).collect();
    let mut result = primes.iter().fold(1, |a, x| a * x);
    let mut pr = primes::Primes::new(20);
    let mut factors = Vec::with_capacity(20);
    for x in vec![4,6,8,10,12,14,15,16,18,20] {
        let mut val = result;
        pr.prime_factors(x, &mut factors);
        for p in factors.iter() {
            if (val % p) == 0 { val /= p } else { result *= p }
        }
        factors.truncate(0);
    }
    println!(
        "smallest positive number that is evenly divisible \
        by all of the numbers from 1 to 20 : {}", result
    );
}
