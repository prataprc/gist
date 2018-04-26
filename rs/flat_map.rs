fn main() {
    let a = 0..3;
    let b = 3..6;
    let c = 6..9;
    let v = vec![a, b, c];
    v.iter().flat_map(|it| it.clone());
}
