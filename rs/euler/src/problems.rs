//use super::problem0001;
//use super::problem0002;
//
//#[allow(non_upper_case_globals)]
//pub const solutions: [fn(); 3] = [
//    || { println!("problem number starts with 1") },
//    problem0001::solve,
//    problem0002::solve,
//];

//static CHAR2DIGIT: [i64; 256] = [
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
//    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
//];


//fn p4() {
//    let mut result: u64 = 0;
//    for i in (99..1000).rev() {
//        for j in (i..1000).rev() {
//            let num = i * j;
//            if is_palindrome(num.to_string().as_bytes()) {
//                if result < num {
//                    result = num;
//                }
//            }
//        }
//    }
//    println!("largest palindrome made from the product of two 3-digit numbers {}", result);
//}
//
//fn p5() {
//    let primes = vec![2,3,5,7,11,13,17,19];
//    let mut result = primes.iter().fold(1, |a, x| a * x);
//    for x in vec![4,6,8,10,12,14,15,16,18,20] {
//        let mut val = result;
//        for p in prime_factors(x) {
//            if (val % p) == 0 { val /= p } else { result *= p }
//        }
//    }
//    println!("smallest positive number that is evenly divisible \
//             by all of the numbers from 1 to 20 {}", result);
//}
//
//fn p6() {
//    let s1 = (1..101).map(|x| x*x).fold(0, |a, x| a+x);
//    let s2 = (1..101).fold(0, |a, x| a+x);
//    println!("difference between the sum of the squares of the first \
//              one hundred natural numbers and the square of the sum: {}", (s2*s2)-s1);
//}
//
//fn p7() {
//    let mut primes: Vec<i64> = vec![2,3,5,7,11,13,17,19];
//    let mut candidate = 20;
//    while primes.len() < 10001 {
//        let till: i64 = ((candidate as f64).sqrt() as i64) + 1;
//        let is_prime = {
//            primes.iter()
//                .take_while(|&p| *p < till)
//                .skip_while(|&p| candidate % *p != 0 ).next().is_none()
//        };
//        if is_prime { primes.push(candidate) }
//        candidate += 1;
//    }
//    println!("{:?}", &primes[10000]);
//}
//
//fn p8() {
//    let inp = "73167176531330624919225119674426574742355349194934\
//               96983520312774506326239578318016984801869478851843\
//               85861560789112949495459501737958331952853208805511\
//               12540698747158523863050715693290963295227443043557\
//               66896648950445244523161731856403098711121722383113\
//               62229893423380308135336276614282806444486645238749\
//               30358907296290491560440772390713810515859307960866\
//               70172427121883998797908792274921901699720888093776\
//               65727333001053367881220235421809751254540594752243\
//               52584907711670556013604839586446706324415722155397\
//               53697817977846174064955149290862569321978468622482\
//               83972241375657056057490261407972968652414535100474\
//               82166370484403199890008895243450658541227588666881\
//               16427171479924442928230863465674813919123162824586\
//               17866458359124566529476545682848912883142607690042\
//               84580156166097919133875499200524063689912560717606\
//               05886116467109405077541002256983155200055935729725\
//               71636269561882670428252483600823257530420752963450";
//    let max = (0..(inp.len()-13))
//        .map(|i| {
//            let bytes = (&inp[i..i+13]).bytes();
//            bytes.fold(1, |a, x| a * (CHAR2DIGIT[x as usize] as i64))
//            // ???
//            //(&inp[i..i+13]).bytes().fold(1, |a, x| a * (CHAR2DIGIT[x as usize] as i64))
//        }).max().unwrap();
//    println!("thirteen adjacent digits in the 1000-digit number \
//             that have the greatest product: {}", max);
//}
//
//fn p9() {
//    let squares: Vec<i32> = (0..1001).map(|x| x*x).collect();
//    for x in squares[0..1001].iter().enumerate() {
//        for y in squares[0..1001].iter().enumerate() {
//            let (i, j) = ((x.0) as i32, (y.0) as i32);
//            if i + j >= 1000 { break }
//            let k = ((x.1 + y.1) as f64).sqrt();
//            if k == k.floor() {
//                let p = i * j * (k as i32);
//                if (i + j + (k as i32)) == 1000  &&  p > 0 {
//                    println!("pythagorean triplet's sum = 1000, product = {}",p);
//                    return;
//                }
//            }
//        }
//    }
//}

