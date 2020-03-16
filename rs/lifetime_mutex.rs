use std::sync::{Mutex, MutexGuard};

struct GlobalCounter {
    count: u64,
}

impl GlobalCounter {
    fn as_count(&self) -> &u64 {
        &self.count
    }
}

struct Counter {
    count1: Mutex<GlobalCounter>,
    count2: u64,
}

impl Counter {
    fn to_holder(&self) -> Box<Holder> {
        let mut h = Box::new(Holder {
            guard: self.count1.lock().unwrap(),
            refp: None,
        });
        h.refp = Some(h.guard.as_count());
        h
    }
}

struct Holder<'a> {
    guard: MutexGuard<'a, GlobalCounter>,
    refp: Option<&'a u64>,
}

fn main() {
    let c = Counter {
        count1: Mutex::new(GlobalCounter { count: 100 }),
        count2: 200,
    };
    let h: Box<Holder> = c.to_holder();
    println!("{}", h.refp.is_some());
}
