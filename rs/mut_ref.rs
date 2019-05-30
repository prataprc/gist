struct Ty {
    x: i32,
    list: Vec<Ty>,
}

struct Tx<'a> {
    field: &'a mut Ty,
}

fn main() {
    let mut a = Ty {
        x: 10,
        list: vec![
            Ty {
                x: 20,
                list: vec![],
            },
            Ty {
                x: 20,
                list: vec![],
            },
        ],
    };
    println!("{:p}", get(&mut a, 1));

    let b = Tx { field: &mut a };
    b.field.x = 10;
    println!("{}", b.field.x);
}

fn get(mut ptr: &mut Ty, idx: usize) -> &mut Ty {
    for i in 0..idx {
        ptr = &mut ptr.list[i]
    }
    return ptr;
}
