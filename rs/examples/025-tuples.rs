// A tuple is a collection of values of different types. Tuples
// are constructed using parantheses (), and each tuple itself
// is a value with type signature (T1, T2, ...), where T1, T2
// are the types of its members.
//
// Functions can use tuples to return multiple values, as
// tuples can hold any number of values.

fn reverse(pair: (i32, bool)) -> (bool, i32) {
    let (integer, boolean) = pair;
    (boolean, integer)
}

fn main() {
    let long_tuple = (1u8, 2u16, 3u32, 4u64, -1i8, -2i16,
                      -3i32, -4i64, 0.1f32, 0.2f64, 'a', true);

    // values can be extracted from the tuple using tuple indexing.
    println!("long tuple first value: {}", long_tuple.0);
    println!("long tuple second value: {}", long_tuple.1);

    // Tuples can be tuple members
    let tuple_of_tuples = ((1u8, 2u16, 2u32), (4u64, -1i8), -2i16);

    // Tuples are printable
    println!("tuple of tuples: {:?}", tuple_of_tuples);

    let pair = (1, true);
    println!("pair is {:?}", pair);

    println!("the reverse pair is {:?}", reverse(pair));

    // To create one element tuple, the comma is required to tell
    // them apart from the a literal surrounded by parantheses
    println!("one element tuple: {:?}", (5u32,));
    println!("just an integer: {:?}", (5u32));
}
