fn main() {
    // there are two types of statmemt.
    let mut _x = 20; // the let statement.
    _x += 2; // the expression statement.
    // expression statement is constructed by suffixing an expression with `;`
    // otherwise everything is an expression, including assignment
    let mut _y;
    _y = _x = 30; // y will be unity, instead of 30

    // blocks are expressions too.
    _y = { 40; _x += 20 } // _y has the value of last expression in the block
}
