use std::ops::Drop;
use std::sync::atomic::AtomicPtr;

#[derive(Debug)]
struct Mytype(i128);

impl Drop for Mytype {
    fn drop(&mut self) {
        println!("dropped mytype {}", self.0);
    }
}

#[derive(Debug)]
struct Container {
    val: i128,
    ptr: AtomicPtr<Mytype>,
}

impl Drop for Container {
    fn drop(&mut self) {
        println!("dropped container {}", self.val);
    }
}

fn main() {
    {
        let a = Box::new(Mytype(10));
        let b = Box::new(Mytype(20));
        println!("{:?} {:?}", a, b);
        let c = Container {
            val: 100,
            ptr: AtomicPtr::new(Box::into_raw(b)),
        };

        println!("{:?}", c);
    }
}
