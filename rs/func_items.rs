mod modx {
    static X: i32 = 10;
    pub fn items_in_function() {
        // can contain,
        //      - extern crate declaration
        //      - use declaration
        //      - module definition
        extern crate std;
        use mody::Y as y;
        mod mod_fn_nested { // pub qualifier does not have an effect here.
            pub static Z: i32 = 30;
        }
        println!("print X from parent scope: {}", X);
        println!("print y from parent's sibling: {}", y);
        println!("print z from function's nested_mod: {}", mod_fn_nested::Z);

        // can contain,
        //      - type definition
        //      - struct definition
        //      - enum definition
        //      - trait definition
        type M = u32;
        #[derive(Debug)]
        struct S(u32, i32);
        #[derive(Debug)]
        enum E {
            E1(u32),
            E2(String),
        }
        println!("function local type: {:?}", 10 as M);
        println!("function local struct: {:?}", S(10, 20));
        println!("function local enum.E1: {:?}", E::E1(20));
        println!("function local enum.E2: {:?}", E::E2("str".to_string()));

        // can contain,
        //      - function definition
        //      - implementations
        fn nested_fn() {
            println!("nested function");
        }
        impl S {
            fn m_method(self) {
                println!("m_method for {:?}", self);
            }
        }
        let s = S(1000, 2000);
        nested_fn();
        s.m_method();

        // finally static items are allowd within function.
        static fn_static: &'static str = "I am static in function";
        println!("function local static: {}", fn_static);
    }
}

pub mod mody {
    pub static Y: i32 = 20;
}

fn main() {
    modx::items_in_function();
    // modx::X <- X is not public.
}
