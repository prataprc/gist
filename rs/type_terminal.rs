use std::mem;

#[derive(Debug,PartialEq)]
struct TerminalType1;
#[derive(Debug,PartialEq)]
struct TerminalType2;

fn main() {
    println!("{:?}: {:p}", TerminalType1, &TerminalType1);
    println!("{:?}: {:p}", TerminalType1, &TerminalType2);
    what_is_terminal_type1(TerminalType1, 10);
    what_is_terminal_type2(TerminalType2, 20);
}

fn what_is_terminal_type1(x: TerminalType1, arg2: u8) {
    println!(
        "received TerminalType1 {:?}: {:p}/{:p} {}, size={}",
        x, &x, &arg2, x == TerminalType1, mem::size_of::<TerminalType1>());
}

fn what_is_terminal_type2(x: TerminalType2, arg2: u8) {
    println!(
        "received TerminalType2 {:?}: {:p}/{:p} {}, size={}",
        x, &x, &arg2, x == TerminalType2, mem::size_of::<TerminalType2>());
}
