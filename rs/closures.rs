fn main() {
    // Examples of closures.
    let plus_one = |x: i32| x + 1;
    let plus_two = |x: i32| {
        let mut result = x;
        result += 1;
        result += 1;
        result
    };
    println!("plus_one of 10: {}", plus_one(10));
    println!("plus_two of 10: {}", plus_two(10));

    // can write iterator-adaptors (closures) for Option enum.
    {
        let option = Some(10);
        let new1 = option.map(|x| x + 20);
        let new2 = option.map(|x| x + 30);
        println!("option_closure new1 {:?}", new1);
        println!("option_closure new2 {:?}", new2);
    }

    // cannot borrow `_num` as mutable because it is also borrowed as
    // immutable
    {
        let mut _num = 5;
        let _plus_num = |x: i32| x + _num;
        let _y = &_num;
        // let _y = &mut _num; <- FAIL: not allowed
    }

    // ownership of nums is taken by `_takes_nums`;
    {
        let _nums = vec![1, 2, 3];
        let _takes_nums = || _nums;
        // println!("{:?}", _nums); <- FAIL: use of moved value _nums
    }

    scoped_borrow();
    move_closure();
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
