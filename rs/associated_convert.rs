use std::marker::PhantomData;

trait MeasurementUnit<T> {
    const RATIO: f64;
}

#[derive(Debug, PartialEq, Clone, Copy)]
struct Measure<Unit> {
    value: f64,
    phantom: std::marker::PhantomData<Unit>,
}

#[derive(Clone)]
struct Inch;
impl MeasurementUnit<Foot> for Inch {
    const RATIO: f64 = 1.;
}

#[derive(Clone)]
struct Foot;
impl MeasurementUnit<Inch> for Foot {
    const RATIO: f64 = 12.;
}

struct Hour;
impl MeasurementUnit<Second> for Hour {
    const RATIO: f64 = 3600.;
}

#[derive(Clone)]
struct Second;
impl MeasurementUnit<Hour> for Second {
    const RATIO: f64 = 1.;
}

impl<T> Measure<T> {
    fn convert<U>(&self) -> Measure<U>
    where
        T: MeasurementUnit<U>,
        U: MeasurementUnit<T>,
    {
        Measure::<U> {
            value: self.value * (T::RATIO / U::RATIO),
            phantom: PhantomData,
        }
    }
}

fn main() {
    let m1 = Measure::<Foot> {
        value: 7.2,
        phantom: PhantomData,
    };
    let m2: Measure<Inch> = m1.clone().convert();
    println!("{} feet are {} inches.", m1.value, m2.value);

    let m3 = Measure::<Second> {
        value: 3600.0,
        phantom: PhantomData,
    };
    let m4: Measure<Hour> = m3.convert::<Hour>();
    println!("{} seconds are {} hours.", m3.value, m4.value);

    //let m3: Measure<Hour> = m1.convert::<Hour>();
    //println!("{} feet are {} hours.", m1.value, m3.value);
}
