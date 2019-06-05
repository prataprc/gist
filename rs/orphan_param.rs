//Type annotation for associated constants.
//
//I have a situation where I need to club related constants with a type
//and the type is parametrised over `V`. Now when I use the constant
//outside the type's impl, like the example given below:
//
//```
struct Value<V> {
    value: V,
}

impl<V> Value<V> {
    const VALUE_FLAG: u64 = 0x1000000000000000;
}

fn main() {
    let x = 0x20 | Value::<()>::VALUE_FLAG;
    println!("{}", x);
}
//```
//
//I get following error:
