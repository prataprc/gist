use primes::Primes;

/// The prime factors of 13195 are 5, 7, 13 and 29.
/// What is the largest prime factor of the number 600851475143 ?
pub fn solve() {
    let num = 600851475143_u64;
    let mut prime = Primes::new(num);
    let mut factors = Vec::with_capacity(1000);
    prime.prime_factors(num, &mut factors);
    println!(
        "largest prime factor of the number 600851475143: {:?}",
        factors[factors.len()-1],
    );
}
