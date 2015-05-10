fn main() {
    let plus_one = |x: i32| x + 1;
    let plus_two = |x: i32| {
        let mut result = x;
        result += 1;
        result += 1;
        result
    };

    println!("plus_one of 10: {}", plus_one(10));
    println!("plus_two of 10: {}", plus_two(10));
    borrowing_mutables();
    taking_ownership();
    scoped_borrow();
    move_closure();
    option_closure();
}

fn option_closure() {
    let option = Some(10);
    let new1 = option.map(|x| x + 20);
    let new2 = option.map(|x| x + 30);
    println!("option_closure new1 {:?}", new1);
    println!("option_closure new2 {:?}", new2);
}

fn borrowing_mutables() {
    let mut _num = 5;
    let _plus_num = |x: i32| x + _num;
    let _y = &_num;
    // FIXME: cannot borrow `_num` as mutable because it is also borrowed as
    // immutable
    // let _y = &mut _num;
}

fn taking_ownership() {
    let _nums = vec![1, 2, 3];
    let _takes_nums = || _nums;
    // FIXME: ownership of nums is taken by `_takes_nums`
    // println!("{:?}", nums);
}

fn scoped_borrow() {
    let mut num = 5;
    {
        let mut add_num = |x: i32| num += x;
        add_num(5);
    }
    assert_eq!(10, num);
}

fn move_closure() {
    let mut num = 5;
    {
        let mut add_num = move |x: i32| num += x;
        add_num(5);
    }
    assert_eq!(5, num);
}
