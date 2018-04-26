//use super::problem0001;
//use super::problem0002;
//
//#[allow(non_upper_case_globals)]
//pub const solutions: [fn(); 3] = [
//    || { println!("problem number starts with 1") },
//    problem0001::solve,
//    problem0002::solve,
//];



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

