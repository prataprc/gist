fn main() {
    let mut b = BinaryTreeArray::new(1);

    for d in &mut b.iter_mut() {
        d.data = 2;
    }
}

pub struct BinaryTreeNode<T> {
    pub data: T,
    l: usize,
    r: usize,
}

impl<T> BinaryTreeNode<T> {
    pub fn new(data: T) -> Self {
        Self { data, l: 0, r: 0 }
    }

    #[inline]
    pub fn is_leaf(&self) -> bool {
        self.l == 0 && self.r == 0
    }
}

pub struct BinaryTreeArray<T> {
    nodes: Vec<BinaryTreeNode<T>>,
}

impl<T> BinaryTreeArray<T> {
    pub fn new(data: T) -> Self {
        Self {
            nodes: vec![BinaryTreeNode::new(data)],
        }
    }

    #[inline]
    pub fn get(&self, index: usize) -> Option<&BinaryTreeNode<T>> {
        self.nodes.get(index)
    }

    #[inline]
    pub fn get_mut(&mut self, index: usize) -> Option<&mut BinaryTreeNode<T>> {
        self.nodes.get_mut(index)
    }

    pub fn iter_mut(&mut self) -> BinaryTreeIteratorMut<'_, T> {
        BinaryTreeIteratorMut::new(self)
    }
}

pub struct BinaryTreeIteratorMut<'a, T> {
    tree: &'a mut BinaryTreeArray<T>,
    nodes: Vec<usize>,
}

impl<'a, T> BinaryTreeIteratorMut<'a, T> {
    pub fn new(tree: &'a mut BinaryTreeArray<T>) -> Self {
        Self {
            tree,
            nodes: vec![0],
        }
    }
}

impl<'a, T> Iterator for BinaryTreeIteratorMut<'a, T> {
    type Item = &'a mut BinaryTreeNode<T>;

    fn next(&mut self) -> Option<&'a mut BinaryTreeNode<T>> {
        let Some(index) = self.nodes.pop();
        let some_node: Option<&'a mut BinaryTreeNode<T>> = self.tree.get_mut(index);
        if let Some(node) = some_node {
            if node.r != 0 {
                self.nodes.push(node.r);
            }
            if node.l != 0 {
                self.nodes.push(node.l);
            }
            return Some(node);
        }
        None
    }
}
