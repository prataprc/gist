#![allow(unstable_features)]
#![feature(lang_items,unboxed_closures, core)]

fn main() {
    sugared();
    unsugared();
}

fn sugared() {
    let num = 5;
    let plus_num = |x: i32| x + num;
    println!("sugared {}", plus_num(10));
}

fn unsugared() {
    let num: i32 = 5;
    // unsugared for :: let plus_num = |x: i32| x + num;
    struct ClosureAnon1<'a> { closed_num: &'a i32 };
    impl<'a> FnOnce<(i32,)> for ClosureAnon1<'a> {
        type Output = i32;
        extern "rust-call" fn call_once(self, (x,): (i32,)) -> i32 { x + *self.closed_num }
    }
    // unsugared ends here.

    let plus_num = ClosureAnon1{closed_num: &num};
    println!("sugared {}", plus_num(10));
}
