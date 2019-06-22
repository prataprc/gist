#![allow(unused)]
fn main() {
    use std::mem::ManuallyDrop;
    struct Peach;
    struct Banana;
    struct Melon;
    struct FruitBox {
        // Immediately clear there’s something non-trivial going on with these fields.
        peach: ManuallyDrop<Peach>,
        melon: Melon, // Field that’s independent of the other two.
        banana: ManuallyDrop<Banana>,
    }

    impl Drop for Peach {
        fn drop(&mut self) {
            println!("peach dropped");
        }
    }

    impl Drop for Banana {
        fn drop(&mut self) {
            println!("banana dropped");
        }
    }

    impl Drop for Melon {
        fn drop(&mut self) {
            println!("melon dropped");
        }
    }

    impl Drop for FruitBox {
        fn drop(&mut self) {
            println!("fruitbox dropped enter");
            unsafe {
                // Explicit ordering in which field destructors are run specified in the intuitive
                // location – the destructor of the structure containing the fields.
                // Moreover, one can now reorder fields within the struct however much they want.
                //ManuallyDrop::drop(&mut self.peach);
                //ManuallyDrop::drop(&mut self.banana);
            }
            // After destructor for `FruitBox` runs (this function), the destructor for Melon gets
            // invoked in the usual manner, as it is not wrapped in `ManuallyDrop`.
            println!("fruitbox dropped exit");
        }
    }
    let x = FruitBox {
        // Immediately clear there’s something non-trivial going on with these fields.
        peach: ManuallyDrop::new(Peach),
        melon: Melon, // Field that’s independent of the other two.
        banana: ManuallyDrop::new(Banana),
    };
}
