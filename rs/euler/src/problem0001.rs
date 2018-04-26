// If we list all the natural numbers below 10 that are multiples of 3 or 5,
// we get 3, 5, 6 and 9. The sum of these multiples is 23. Find the sum of
// all the multiples of 3 or 5 below 1000.
pub fn solve() {
    let result = (0..1000).fold(
        0_u32,
        |acc, n| { if (n%3) == 0 || (n%5) == 0 { return acc + n }; acc }
    );
    println!("the sum of all the multiples of 3 or 5 below 1000: {}", result);
}
