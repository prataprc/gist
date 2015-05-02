// There are three types of structures ("structs") that can be created
// using the struct keyword:
//      * tuple structs, which are basically named tuples
//      * the classic C structs
//      * unit structs, which are field-less are useful for generics

// A unit struct;
struct Nil;

// A tuple strucut
struct Pair(i32, f64);

// A struct with two fields
struct Point {
    x: f64,
    y: f64,
}

// structs can be reused as fields of another struct.
#[allow(dead_code)]
struct Rectangle {
    p1: Point,
    p2: Point,
}

// visibility of structure within modules.
mod my {
    // a public struct with public fields.
    pub struct WhiteBox<T> {
        pub contents: T,
    }

    // a public struct with private fields.
    #[allow(dead_code)]
    pub struct BlackBox<T> {
        contents: T,
    }

    impl<T> BlackBox<T> {
        // a public constructor
        pub fn new(contents: T) -> BlackBox<T> {
            BlackBox{contents: contents}
        }
    }
}

fn main() {
    let point: Point = Point{x: 0.3, y: 0.4};
    println!("point coordinates: ({}, {})", point.x, point.y);

    // de-structure the point using a `let` binding
    let Point{x: my_x, y: my_y} = point;

    let _rectangle = Rectangle{
        p1: Point{x: my_y, y: my_x},
        p2: point,
    };

    let _nil = Nil;
    let pair = Pair(1, 0.1);
    let Pair(integer, decimal) = pair;

    println!("pair contains {:?} and {:?}", integer, decimal);

    // public structs with public fields can be constructed as usual.
    let white_box = my::WhiteBox{contents: "public informat"};

    // and their fields can be normally accessed
    println!("The white box contains: {}", white_box.contents);

    // but public structs with private fields can't be constructed
    // let black_box = my::BlackBox{contents: "classified information"};

    // However, structs with private fields can still be created using
    // constructors
    let _black_box = my::BlackBox::new("classified information");

    // The private fields of a struct can't be accessed,
    // println!("The black box contains: {}", _black_box.contents);
}
