#![feature(core_intrinsics)]

use std::io;

fn print_type_of<T>(_: &T) {
    println!("{}", unsafe { std::intrinsics::type_name::<T>() });
}

fn main() {
    // guessit()
    print_type_of(&32.90);          // prints "f64"
    print_type_of(&vec![1, 2, 4]);  // prints "std::vec::Vec<i32>"
    print_type_of(&"foo");          // prints "&str"
}

fn guessit() {
    println!("Guess the number!");
    println!("Please input your guess.");

    let mut guess = String::new();
    io::stdin().read_line(&mut guess).expect("Failed to read line");

    println!("You guessed: {}", guess);
}
