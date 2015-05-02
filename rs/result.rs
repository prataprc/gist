enum Rt<T, E> {
    Ot(T),
    Et(E),
}

fn mutate(r: &mut Rt<&mut i32, &mut i32>) -> i32 {
    match r {
        &mut Rt::Ot(_) => 42,
        &mut Rt::Et(_) => 0,
    }
}

fn main() {
    let mut x = Rt::Ot(&mut 2);
    mutate(&mut x);
}
