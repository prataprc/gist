use std::collections::HashMap;

fn main() {
    let mut a: HashMap<u64, u32> = HashMap::new();
    let mut b: HashMap<u64, u32> = HashMap::new();
    a.into_iter().map(|(k, v)| b.insert(k, v));
}
