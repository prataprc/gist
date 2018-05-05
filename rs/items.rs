#[derive(Debug)]
struct X {
    a: u32,
}

type Y = X;

union Z {
    a: u32,
    b: u32,
}

#[derive(Debug)]
enum AB {
   X(u32, u32),
   Y{a: u32, b:u32},
   Z,
}

const data_c: u32 = 20;
static data_s: u32 = 2000;

mod xyz {
    pub static data_s: u32 = 20;
}

trait Tt {
    const x: u32 = 10;
    fn tfn() -> u32 {
        Self::x
    }
}

impl X {
    const x: u32 = 10;
    fn ifn() -> u32 {
        Self::x
    }
}

impl Tt for X {
}

fn main() {
    let a = X{a: 200};
    let b: &Y = &a;
    let mut c = Z{a: 10};
    let d = AB::X(1,2);
    let e = AB::Y{a:1, b:2};
    let f = AB::Z;
    let t: u32;

    unsafe { t = c.a }
    println!("{:?} {:?} {:?}", data_c, data_s, xyz::data_s);
    println!("{:?} {:?} {:?} {:?} {:?} {:?}", a, b, t, d, e, f);
    println!("{:?} {:?}", X::x, Tt.tfn());
    c.b = 20;
}

