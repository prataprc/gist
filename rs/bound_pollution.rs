use std::fmt::Debug;

#[derive(Clone)]
struct S(i32);

struct Mytype<K>
where
    K: Clone,
{
    a: K,
}

impl<K> Mytype<K>
where
    K: Clone,
{
    fn new(k: K) -> Mytype<K> {
        Mytype { a: k }
    }

    fn value(&self) -> i32 {
        10
    }
}

impl<K> Mytype<K>
where
    K: Clone + Debug,
{
    fn validate(&self) -> String {
        format!("{:?}", self.a)
    }
}

fn main() {
    let a = Mytype::new(S(10));
    println!("{}", a.value());
}
