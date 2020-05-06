use std::marker;

pub struct ResultSet<'r> {
    _ref: *mut [u8],
    _phantom_data: marker::PhantomData<&'r ()>,
}

impl<'r> Iterator for ResultSet<'r> {
    type Item = Row<'r>;

    fn next(&mut self) -> Option<Row<'r>> {
        unsafe {
            Some(Row{
                rset: self._ref.as_ref().unwrap()
            })
        }
    }
}

/** A single result row from a Query. */
pub struct Row<'r> {
    rset: &'r [u8]
}

fn main() {
    let blob = vec![10_u8,20_u8];
    let mut results = ResultSet{
        _ref: blob.as_slice() as *const [u8] as *mut [u8],
        _phantom_data: marker::PhantomData,
    };
    let _row = results.next();
}
