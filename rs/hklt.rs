fn call_on_ref_zero__<'a, F>(f: F) where F: Fn(&'a i32) {
    let zero = 0;
    f(&zero);
}

fn call_on_ref_zero<F>(f: F) where for<'a> F: Fn(&'a i32) {
    let zero = 0;
    f(&zero);
}

fn main() {
    println!("hello world")
}
