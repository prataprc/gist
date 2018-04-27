use primes;

/// By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13,
/// we can see that the 6th prime is 13.
///
/// What is the 10001st prime number?
pub fn solve() {
    for (i, p) in primes::Primes::new(1000000000).enumerate() {
        if i == 10000 {
            println!("What is the 10001st prime number? {}", p);
            return
        }
    }
    panic!("unreachable code");
}
