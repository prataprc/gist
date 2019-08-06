use std::any::Any;
use std::fmt::{Debug, Display, Error, Formatter};

trait MoltAny: Any + Display + Debug + Clone + Copy {
    fn as_any(&self) -> &dyn Any;
    fn as_any_mut(&mut self) -> &mut dyn Any;
    fn into_any(self: Box<Self>) -> Box<dyn Any>;
}

#[derive(Debug, Clone, Copy)]
struct X;

impl MoltAny for X {
    fn as_any(&self) -> &dyn Any {
        self
    }

    fn as_any_mut(&mut self) -> &mut dyn Any {
        self
    }

    fn into_any(self: Box<Self>) -> Box<dyn Any> {
        self
    }
}

impl Display for X {
    fn fmt(&self, _f: &mut Formatter) -> Result<(), Error> {
        Ok(())
    }
}

fn main() {
    let x = X;
    println!("hello world");
    myfunc(Box::new(x));
}

fn myfunc<T: MoltAny>(t: Box<T>) {
    println!(
        "myfunc {:?} {:?}",
        t.clone().into_any().type_id(),
        t.as_any().downcast_ref::<X>()
    );
}
