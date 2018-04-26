mod math;
mod primes;
mod fibonacci;
mod problem0001;
mod problem0002;
mod problem0003;

#[allow(non_upper_case_globals)]
pub const solutions: [fn(); 4] = [
    || { println!("problem number starts with 1") },
    problem0001::solve,
    problem0002::solve,
    problem0003::solve,
];
