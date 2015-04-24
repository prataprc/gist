fn main() {
    let if_res = do_if();
    let loop_res = try_loop();
    println!("if result {}", if_res);
    println!("loop result {}", loop_res);
}

fn do_if() -> &'static str {
    let n = 5;
    if n < 5 {
        "less than 5"
    } else if n > 5 {
        "greater than 5"
    } else {
        "equal to 5"
    }
}

fn try_loop() -> u32 {
    let mut count = 0;
    'outer: loop {
        if count == 10 {
            count += 10;
            continue;
        } else if count > 100 {
            return count;
        }
        count += 1
    }
}
