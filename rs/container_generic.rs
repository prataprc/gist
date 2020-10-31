trait Node<L> {
    fn get(&self, key: usize) -> &Kind<L>;
}

enum Kind<L> {
    List(L),
}

impl<V> Node<Self> for Vec<V> {
    fn get(&self, key: usize) -> &V {
        &self[key]
    }
}

fn main() {
    println!("hello world")
}
