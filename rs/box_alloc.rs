use std::io::stdin;
use std::ops::{Deref, Drop};
use std::sync::atomic::AtomicPtr;

#[derive(Debug)]
struct Mytype(i128);

impl Drop for Mytype {
    fn drop(&mut self) {
        println!("dropped {}", self.0);
    }
}

fn main() {
    {
        let a = alloc_atomic();
        println!("in main atomic {:?}", a);
        let mut s = String::new();
        stdin().read_line(&mut s);
    }
    println!("");

    {
        let local = Mytype(1);
        println!("alloc main {:?} {:p}", local, &local);
        let (local1, local2, local3) = alloc_box(local);
        println!("in main a {:?} {:?} {:?}", local1, local2, local3);
        println!(
            "in main a {:p} {:p} {:p}",
            &local1,
            local2.deref(),
            local3.deref(),
        );
        let mut s = String::new();
        stdin().read_line(&mut s);
    }

    let mut s = String::new();
    stdin().read_line(&mut s);
}

fn alloc_atomic() -> AtomicPtr<Mytype> {
    let a = Box::new(Mytype(10));
    println!("alloc atomic {:?}", a);
    AtomicPtr::new(Box::into_raw(a))
}

fn alloc_box(local: Mytype) -> (Mytype, Box<Mytype>, Box<Mytype>) {
    let local1 = Mytype(20);
    let local2 = Box::new(Mytype(30));
    let a = Box::new(local);
    println!("alloc box {:?} {:?}", local1, local2);
    println!("alloc box {:p} {:p}", &local1, local2.deref());
    (local1, local2, a)
}

//alloc atomic Mytype(10)
//in main atomic 0x55b0aaeeea40
//
//alloc main Mytype(1) 0x7ffdd65667b8
//alloc box Mytype(20) Mytype(30)
//alloc box 0x7ffdd6566490 0x55b0aaef0c80
//in main a Mytype(20) Mytype(30) Mytype(1)
//in main a 0x7ffdd6566830 0x55b0aaef0c80 0x55b0aaef0ca0
//
//dropped 1
//dropped 30
//dropped 20
