extern crate num;

use std::iter::{Iterator};
use std::ops::{Rem,Div,Add};
use self::num::{ToPrimitive,FromPrimitive};
use std::fmt::{Display,Debug};

pub struct Primes<T> {
    from: T,
    till: T,
    cached: Vec<T>,
    idx: usize,
    one: T,
}

impl<T> Primes<T>
    where T:Display + Debug +
            Copy + Default + PartialEq + PartialOrd +
            Add<Output=T> + Rem<Output=T> + Div<Output=T> +
            FromPrimitive + ToPrimitive
{
    pub fn new(till: T) -> Primes<T> {
        let one = T::from_u32(1).unwrap();
        let mut cached: Vec<T> = Vec::with_capacity(1000);
        cached.push(T::from_u32(2).unwrap());
        Primes{from: one, till, cached, idx: 0, one}
    }

    pub fn is_prime(num: T, primes: &[T]) -> bool {
        let ptill = (num.to_f64().unwrap().sqrt() as i64) + 1;
        let ptill = T::from_i64(ptill).unwrap();
        let zero = T::from_u32(0).unwrap();
        let ok = primes.iter()
                       .take_while(|&&p| p < ptill)
                       .any(|&p| (num%p) == zero);
        //println!("isprime {} {}", num, !ok);
        !ok
    }

    pub fn reload(&mut self, till: T) {
        self.from = self.one;
        self.till = till;
        self.idx = 0;
        //println!("reload {:?}", self.cached);
    }

    pub fn prime_factors(&mut self, num: T, factors: &mut Vec<T>) {
        let mut num = num;
        self.reload(num);
        loop {
            match self.next() {
                Some(p) if num%p == T::default() => {
                    factors.push(p);
                    num = num / p;
                    self.reload(num);
                    //println!("{} {}", p, num);
                },
                Some(_) => continue,
                None => return,
            }
        }
    }
}

impl<T> Iterator for Primes<T>
    where T:Display + Debug +
            Copy + Default + PartialEq + PartialOrd +
            Add<Output=T> + Rem<Output=T> + Div<Output=T> +
            FromPrimitive + ToPrimitive
{
    type Item=T;

    fn next(&mut self) -> Option<T> {
        if self.idx >= self.cached.len() {
            if !self.cached.is_empty() {
                self.from = self.cached[self.cached.len()-1];
            }
            while self.from < self.till {
                self.from = self.from + T::from_u32(1).unwrap();
                let num = self.from;
                if Self::is_prime(num, self.cached.as_slice()) {
                    self.idx += 1;
                    self.cached.push(self.from);
                    return Some(self.from);
                }
            }
            return None
        }

        let result = Some(self.cached[self.idx]);
        self.idx += 1;
        result
    }
}
