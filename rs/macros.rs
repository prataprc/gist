macro_rules! cfor {
    ($init: stmt; $cond: expr; $step: expr; $body: block) => {
        {
            $init;
            while $cond {
                $body;
                $step;
            }
        }
    }
}

fn main() {
    let mut sum = 0;
    cfor!(let mut i = 1_u64; i < 1001; i += 1; {
        sum += i;
    });
    println!("sum: {}", sum);
}
