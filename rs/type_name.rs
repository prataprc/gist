#![feature(core)]

fn main() {
    name(&10);
}

fn name<T>(_: T) -> &'static str {
    let name = unsafe { std::intrinsics::type_name::<T>()};
    name
}
