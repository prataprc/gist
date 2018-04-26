use std::ops::{Add};
use std::fmt::{Debug};
use std::cmp::{PartialOrd};

#[derive(Debug)]
pub struct Fibonacci<T: Add<Output=T>+Copy+Debug+PartialOrd> {
    curr: T,
    next: T,
    till: T,
    initial: (T, T),
}

impl<T> Fibonacci<T>
    where T: Add<Output=T>+Copy+Debug+PartialOrd
{
    pub fn new(curr: T, next: T, till: T) -> Self {
        Fibonacci{curr, next, till, initial:(curr,next)}
    }

    #[allow(dead_code)]
    fn reload(&mut self, till: T) {
        self.curr = self.initial.0;
        self.next = self.initial.1;
        self.till = till;
    }
}

impl<T> Iterator for Fibonacci<T>
    where T: Add<Output=T>+Copy+Debug+PartialOrd
{
    type Item=T;

    fn next(&mut self) -> Option<T> {
        if self.curr < self.till {
            let curr = self.curr;
            self.curr = self.next;
            self.next = curr+self.next;
            return Some(curr)
        }
        None
    }
}
