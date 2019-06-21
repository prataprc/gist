use std::marker::PhantomData;

struct Foo<T, U>(T, PhantomData<U>);

impl<T: AsRef<[U]>, U> Foo<T, U> {
    fn new(value: T) -> Self {
        Foo(value, PhantomData)
    }
}

trait FooImpl {
    fn do_it(&self);
}

impl<T: AsRef<[u8]>> FooImpl for Foo<T, u8> {
    fn do_it(&self) {
        println!("I am a u8!");
    }
}

impl<T: AsRef<[f32]>> FooImpl for Foo<T, f32> {
    fn do_it(&self) {
        println!("I am a f32!");
    }
}

fn do_foo<T: FooImpl>(foo: T) {
    foo.do_it();
}

fn main() {
    Foo::new([42u8]).do_it();
    Foo::new(&[42u8]).do_it();
    Foo::new(vec![42u8]).do_it();
    Foo::new(&vec![42u8]).do_it();

    Foo::new([42.0f32]).do_it();
    Foo::new(&[42.0f32]).do_it();
    Foo::new(vec![42.0f32]).do_it();
    Foo::new(&vec![42.0f32]).do_it();

    do_foo(Foo::new([42u8]));
}
