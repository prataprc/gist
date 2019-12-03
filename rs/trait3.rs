trait X<I>
where
    I: std::ops::Add,
{
    fn double(&self, obj: I) -> I;
}

struct MyT(u32);

impl X<i32> for MyT {
    fn double(&self, obj: i32) -> i32 {
        obj + obj
    }
}

impl X<i64> for MyT {
    fn double(&self, obj: i64) -> i64 {
        obj + obj
    }
}

fn main() {
    let val = MyT(10);
    println!("{}", val.double(10));
}
