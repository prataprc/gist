/// A Pythagorean triplet is a set of three natural numbers,
///     a < b < c, for which, a*a + b*b = c*c
/// For example, 3*3 + 4*4 = 9 + 16 = 25 = 5*5.
///
/// There exists exactly one Pythagorean triplet for which a + b + c = 1000.
/// Find the product abc.
pub fn solve() {
    let squares: Vec<(u32,u32)> = (1u32..1_001).map(|x| (x, x*x)).collect();
    let squares = squares.as_slice();
    for (a, sqa) in squares.iter() {
        for (b, sqb) in squares.iter() {
            let c = 1000 - a - b;
            if c <= 0 {
                break;
            } else if c*c == (sqa+sqb) {
                println!("pythagorean triplet's product : {}", a*b*c);
                return
            }
        }
    }

}
