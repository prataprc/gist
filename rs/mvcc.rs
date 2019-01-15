#[derive(Debug)]
struct Node<'a> {
    data: i32,
    left: Option<&'a Node<'a>>,
    right: Option<&'a Node<'a>>,
}

impl<'a> Node<'a> {
    fn new(data: i32, left: Option<&'a Node<'a>>, right: Option<&'a Node<'a>>) -> Node<'a> {
        Node { data, left, right }
    }
}

fn main() {
    let n = make_tree();
    println!("{:?}", n);
}

fn make_tree<'a>() -> Node<'a> {
    let left = Box::new(Node::new(20, None, None));
    let right = Box::new(Node::new(30, None, None));
    Node::new(10, Some(&left), Some(&right))
}
