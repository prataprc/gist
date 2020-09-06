trait X<I>
where
    I: std::ops::Add + Copy,
{
    fn double(&self, obj: I) -> <I as std::ops::Add>::Output;
}

struct MyT(u32);

impl<I> X<I> for MyT
where
    I: std::ops::Add + Copy,
{
    fn double(&self, obj: I) -> <I as std::ops::Add>::Output {
        obj + obj
    }
}

//impl X<i64> for MyT {
//    fn double(&self, obj: i64) -> i64 {
//        obj + obj
//    }
//}

fn main() {
    let val = MyT(10);
    println!("{}", val.double(10));
}
