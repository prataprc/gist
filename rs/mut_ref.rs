struct Ty { x: i32, list: Vec<Ty> }

fn main() {
    let mut a = Ty{x: 10, list: vec![Ty{x: 20, list:vec![]}, Ty{x: 20, list:vec![]}]};
    println!("{:p}", get(&mut a, 1))
}

fn get(mut ptr: &mut Ty, idx: usize) -> &mut Ty {
    for i in 0..idx {
        ptr = &mut ptr.list[i]
    }
    return ptr
}
