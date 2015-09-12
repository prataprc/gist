trait Functor<A, B> {
    fn fmap<F>(self, f: F) -> Self<B> where F: FnOnce(A) -> B;
}

impl<A, B> Option<A> {
    fn fmap<F>(self, f: F) -> Option<B> where F: FnOnce(A) -> B {
        match self {
            Some(a) => Some(f(a)),
            None => None,
        }
    }
}

fn main() {
    let x = Some(10_u64);
    x.fmap(|x| x as u32);
}
