/// The sum of the squares of the first ten natural numbers is,
/// 1*1 + 2*2 + ... + 10*10 = 385
/// The square of the sum of the first ten natural numbers is,
/// (1 + 2 + ... + 10) * (1 + 2 + ... + 10) = 55 * 55 = 3025
/// Hence the difference between the sum of the squares of the
/// first ten natural numbers and the square of the sum is 3025 − 385 = 2640.
///
/// Find the difference between the sum of the squares of the first one
/// hundred natural numbers and the square of the sum.
pub fn solve() {
    let sumofsquare = (1..101).map(|x| x*x).fold(0, |a, x| a+x);
    let sum = (100 * (100+1)) / 2;
    let squareofsum = sum * sum;
    println!(
        "difference between the sum of the squares of the first \
        one hundred natural numbers and the square of the sum: {}",
        squareofsum-sumofsquare,
    );
}
