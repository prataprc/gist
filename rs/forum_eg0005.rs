use std::hash::Hash;

trait MyTrait {
    fn handle();
}

#[derive(Debug, Clone)]
struct ForestErr<T>(T);

#[derive(Debug, Clone)]
enum ForestAuxErr<NodeID: Clone + Eq + Hash, AuxErr: Clone + MyTrait> {
    ForestErr(ForestErr<NodeID>),
    AuxErr(AuxErr),
}

trait ForestAuxErrT<NodeID> {
    fn missing_child(node_id: NodeID) -> Self;
}

impl<NodeID: Clone + Eq + Hash, AuxErr: Clone + MyTrait> From<AuxErr>
    for ForestAuxErr<NodeID, AuxErr>
{
    fn from(aux_error: AuxErr) -> ForestAuxErr<NodeID, AuxErr> {
        ForestAuxErr::AuxErr(aux_error)
    }
}

impl<NodeID: Clone + Eq + Hash, AuxErr: Clone + MyTrait> From<ForestErr<NodeID>>
    for ForestAuxErr<NodeID, AuxErr>
{
    fn from(forest_error: ForestErr<NodeID>) -> ForestAuxErr<NodeID, AuxErr> {
        ForestAuxErr::ForestErr(forest_error)
    }
}

fn main() {
    println!("hello world");
}
