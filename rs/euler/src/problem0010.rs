extern crate primal;

/// The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
/// Find the sum of all the primes below two million.
pub fn solve() {
    let result: usize = primal::Primes::all()
                        .take_while(|&p| p < 2_000_000_000_usize).count();
    //let result: u64 = primes::Primes::new(std::u64::MAX)
    //                    .take_while(|&x| x < 2_000_000_u64)
    //                    .sum();
    println!("Find the sum of all the primes below two million: {}", result);
}
