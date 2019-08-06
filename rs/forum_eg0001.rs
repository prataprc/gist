// represents external crate 1
mod Crate1Trait {

    // main trait describing generic functionality we work with
    pub trait SomeTrait {
        type Error; // error provided by "implementors"

        fn perform(&mut self) -> Result<u8, Self::Error>;
    }
}

// our "library" code using generic SomeTrait

use crate::Crate1Trait::SomeTrait;

// unified errors into an enum
#[derive(Debug)]
enum UnifiedError<S1, S2>
where
    S1: SomeTrait,
    S2: SomeTrait,
{
    ES1(S1::Error),
    ES2(S2::Error),
}

// why is there a conflicting implementation in core???
impl<S1, S2> From<S1::Error> for UnifiedError<S1, S2>
where
    S1: SomeTrait,
    S2: SomeTrait,
{
    fn from(e1: S1::Error) -> Self {
        UnifiedError::ES1(e1)
    }
}

// why is there a conflicting implementation in core???
impl<S1, S2> From<S2::Error> for UnifiedError<S1, S2>
where
    S1: SomeTrait,
    S2: SomeTrait,
{
    fn from(e2: S2::Error) -> Self {
        UnifiedError::ES2(e2)
    }
}

struct Holder<S1, S2>
where
    S1: SomeTrait,
    S2: SomeTrait,
{
    s1: S1,
    s2: S2,
}

impl<S1, S2> Holder<S1, S2>
where
    S1: SomeTrait,
    S2: SomeTrait,
{
    pub fn new(as1: S1, as2: S2) -> Self {
        Holder { s1: as1, s2: as2 }
    }

    pub fn do_with_held(&mut self) -> Result<u8, UnifiedError<S1, S2>> {
        self.s1.perform()?;
        self.s2.perform()?;

        Ok(3)
    }
}

// "implementor" crate for generic trate, used by users of out lib
mod Crate2Structs {

    // specific error for SomeTrait::Error to work with in reality
    #[derive(Debug)]
    struct OurError {
        code: u8,
    }

    impl OurError {
        pub fn new(c: u8) -> Self {
            OurError { code: c }
        }
    }

    // implementors as structs
    #[derive(Debug)]
    pub struct I1;

    #[derive(Debug)]
    pub struct I2;

    impl crate::Crate1Trait::SomeTrait for I1 {
        type Error = OurError;

        fn perform(&mut self) -> Result<u8, Self::Error> {
            Ok(1)
        }
    }

    impl crate::Crate1Trait::SomeTrait for I2 {
        type Error = OurError;

        fn perform(&mut self) -> Result<u8, Self::Error> {
            Err(OurError::new(2))
        }
    }
}

// user code using our library code and a specific implementor

fn main() {
    let mut i1 = crate::Crate2Structs::I1 {};
    let mut i2 = crate::Crate2Structs::I2 {};

    let mut holder = Holder::new(i1, i2);

    let result = holder.do_with_held();

    println!("Result {:?}", result);
}
