// there are two kinds of statements in rust.
//  - let statement for variable binding
//  - any expression that ends with `;`

#[allow(path_statements)]
fn main() {
    // variable binding
    let x = 5;

    // expression statements
    x; // allow(path_statements) is for this line
    x+1;
    15;

    // blocks are expression too, so they can be used as r-values
    // in assignments. the last expression in the block will be
    // assigned to the l-value.
    let y = {
        let x_squared = x * x;
        let x_cube = x_squared * x;
        // this expression will be assigned to `y`
        x_cube + x_squared + x // <- note that `;` is missing
    };

    let z = {
        2 * x; // <- if `;` is present, then it returns unity ()
    };

    println!("x is {:?}", x);
    println!("y is {:?}", y);
    println!("z is {:?}", z);
}
