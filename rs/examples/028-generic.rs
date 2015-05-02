// generic can be declared for,
//      structures (both named tuples and classic C structs)
//      enums      (to create generic sum-types)
//      functions  (to take generic arguments and/or return generic value)
//      implementation (???)
//
// while it is generic in declaration and definition, it shall
// must be specialized when used, but, because of type inference,
// annotation is usually not required.
//
// implementations can be specific on a generic type, and
// implementations themself can be generic

// a generic struct
struct Pair<T> {
    first: T,
    second: T,
}

// A generic function
fn swap<T>(pair: Pair<T>) -> Pair<T> {
    let Pair{first, second} = pair;
    Pair{first:second, second:first}
}

// re-implementing a 2-element tuple as tuple struct
struct Tuple2<T, U>(T, U);

fn main() {
    // Explicity specialize `Pair`
    let pair_of_chars: Pair<char> = Pair::<char>{first: 'a', second: 'b'};

    // Implicitly specialize `Pair`
    let pair_of_ints = Pair{first: 1i32, second:2};

    // Explicitly specialize `Tuple2`
    let _tuple: Tuple2<char, i32> = Tuple2('R', 2);

    // Explicitly specialize `swap`
    let _swapped_pair_of_chars = swap::<char>(pair_of_chars);

    // Implicitly specialize `swap`
    let _swapped_pair_of_ints = swap(pair_of_ints);

    let x = Tup(3.0);
    let y = GenTup(3i32);
    let mut z = GenTup(3.0);
    println!("{} {} {}", x.value(), y.value(), z.add_one());
}

//---- implementations can also be made generic

struct Tup(f64,);
struct GenTup<T>(T,);

impl Tup {
    fn value(&self) -> &f64 {
        let &Tup(ref val) = self;
        val
    }
}

impl <T> GenTup<T> {
    fn value(&self) -> &T {
        let &GenTup(ref value) = self;
        value
    }
}

impl GenTup<f64> {
    fn add_one(&mut self) -> f64 {
        self.0 += 1.0;
        self.0
    }
}
