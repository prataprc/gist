use math;

// A palindromic number reads the same both ways. The largest palindrome
// made from the product of two 2-digit numbers is 9009 = 91 × 99.
// Find the largest palindrome made from the product of two 3-digit numbers.
pub fn solve() {
    let mut result: u64 = 0;
    for i in (100..1000).rev() {
        for j in (i..1000).rev() {
            let num = i * j;
            if math::is_palindrome(num.to_string().as_bytes()) {
                if result < num {
                    result = num;
                }
            }
        }
    }
    println!("largest palindrome made from the product of two 3-digit numbers {}", result);
}
