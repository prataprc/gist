// small example that tries to describe FirstOrder and the lack of
// HigherOrder types in Rust.

#[derive(Debug)]
struct FirstOrder<T> {
    f: T,
}

//#[derive(Debug)]
//struct HigherOrder<T,U> {
//    h: T<U>, // Error: This is not allowed
//}

#[derive(Debug)]
struct NestedType<U> {
    n: FirstOrder<U>
}

fn main() {
    let first = FirstOrder{f: 10};
    println!("{:?}", first);
    //let higher = HigherOrder{h: first}; // Error: this is how it is useful.
    //println!("{:?}", higher);
    let nested = NestedType{n: first}; // we have to be satisfied with this :(
    println!("{:?}", nested);
}
