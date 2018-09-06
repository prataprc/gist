use std::fmt::Debug;

pub type Input<'a, D: 'a> = Box<dyn Pipeline<D,Item=D> + 'a>;

pub trait Pipeline<D,Item=D>: Iterator<Item=D> + Repeater<D>
    where D: Debug + Clone
{
}

pub trait Repeater<D> where D: Debug + Clone {
    fn repeat(&self) -> Input<D>;
}


pub struct Identity<D> where D: Debug + Clone {
    items: Vec<D>,
    offset: usize,
}

impl<D> Repeater<D> for Identity<D> where D: Debug + Clone {
    fn repeat(&self) -> Input<D> {
        Box::new(Identity{items: self.items.clone(), offset:0})
    }
}

impl<D> Iterator for Identity<D> where D: Debug + Clone {
    type Item=D;

    fn next(&mut self) -> Option<D> {
        if self.offset >= self.items.len() { return None }
        let n = self.offset;
        self.offset += 1;
        Some(self.items[n].clone())
    }
}

impl<D> Pipeline<D> for Identity<D> where D: Debug + Clone {
}

fn main() {
    let mut a = Identity{items: vec![1,2,3,4], offset: 0};
    println!("first {:?}", a.next());
}
