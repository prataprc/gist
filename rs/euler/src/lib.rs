mod math;
mod primes;
mod fibonacci;
mod problem0001;
mod problem0002;
mod problem0003;
mod problem0004;
mod problem0005;
mod problem0006;
mod problem0007;
mod problem0008;
mod problem0009;
mod problem0010;
mod problem0011;

#[allow(non_upper_case_globals)]
pub const solutions: [fn(); 12] = [
    || { println!("problem number starts with 1") },
    problem0001::solve,
    problem0002::solve,
    problem0003::solve,
    problem0004::solve,
    problem0005::solve,
    problem0006::solve,
    problem0007::solve,
    problem0008::solve,
    problem0009::solve,
    problem0010::solve,
    problem0011::solve,
];
