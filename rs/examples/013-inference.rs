// type inference engine is pretty smart. It does more that looking
// at the type of the r-value during an initialization. It also
// looks at how the variable is used afterwards to infer its type.

fn main() {
    // because of the annotation, the compiler knows that `elem`
    // has type u8.
    let elem = 5u8;

    // create an empty vector (a growable array).
    let mut vec = Vec::new();
    // At this point the compiler doesn't kow the exact type of `vec`,
    // it just knows that it's a vector of something (`Vec<_>`)

    // Insert `elem` in the vector.
    vec.push(elem);

    // Aha! now the cimpiler know that `vec` is a vector of `u8`s Vec<u8>

    println!("{:?}", vec);
}
