fn main() {
    let nums = vec![10, 20, 30];

    // 1. using `nums` instead of `&num` will move variable nums into
    //    the iteration and hence prevent its usage further withing the
    //    scope.
    for num in &nums { // num: &i32
        println!("num is {}/{}", num, *num);
    }
}
