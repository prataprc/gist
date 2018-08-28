fn main() {
    let vs = vec![1,2,3,4];
    let iter1 = vs.into_iter();
    let iter2 = iter1.cloned();
    iter1.for_each(|x| println!("first {}", x));
    iter2.for_each(|x| println!("first {}", x));
}
