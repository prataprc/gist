fn update(element: i32, immref: &Vec<i32>) -> i32 {
    println!( "{:?} / {:?}", element, immref);
    element // update the value and return the ownership
}

fn main() {
    let mut stuff = vec![1, 2, 3, 4, 5];
    (0..stuff.len()).for_each(|i| { stuff[i] = update(stuff[i], &stuff); });
}

