#![feature(std_misc)]

fn main() {
    what_float(0_f32);
    what_float(-0_f32);
    what_float(1.0_f32 / 0.0);
    what_float(-1.0_f32 / 0.0);
    what_float(0.0_f32 / 0.0);
}

fn what_float(fnum: f32) {
    let (mant, exp, sign) = fnum.integer_decode();
    println!("{} ({} {:x} {:x}) -- {:?}", fnum, sign, exp, mant, fnum.classify());
}
