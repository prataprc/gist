fn main() {
    let (c1, c2, c3, c4) = ('a', 'b', '\x78', '\u{0078}');
    println!("chars {:?} {:?} {:?} {:?}", c1, c2, c3, c4);

    let s1 = "foo";
    let s2 = r#""foo""#;
    let s3 = "foor #\"# bar ";
    let s4 = r##"foor #"# bar "##;
    let s5 = "\x52";
    let s6 = "R";
    let s7 = r"R";
    let s8 = r"\\x52";

    println!(r####""foo" : {}"####, s1);
    println!(r####"r#""foo""# : {}"####, s2);
    println!(r####""foor #\"# bar " : {}"####, s3);
    println!(r####"r##"foor #"# bar "## : {}"####, s4);
    println!(r####""\x52" : {}"####, s5);
    println!(r####""R" : {}"####, s6);
    println!(r####"r"R" : {}"####, s7);
    println!(r####"r"\\x52" : {}"####, s8);
}
