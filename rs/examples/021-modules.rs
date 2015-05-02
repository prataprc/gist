// a module is a collection of items:
//      global-vars
//      functions
//      structs
//      traits
//      types
//      impl
//      blocks
//      other modules

fn function() {
    println!("called `function()`");
}

// A module named `my`
mod my {
    // a module can contain items like functions
    pub fn function() { // public function, default is private.
        println!("called by my::function()");
    }

    fn private_function() {
        println!("called my::private_function()");
    }

    // Items can access other items in the same module
    pub fn indirect_access() {
        println!("called `my::indirect_access()`, that\n");
        // regardless of their visibility
        private_function();
    }

    // modules can be nested
    pub mod nested { // public module, default is private
        pub fn function() {
            println!("called by my::nested:function()");
            // function(); FIXME: refers to my::nested::function()
        }

        #[allow(dead_code)]
        fn private_function() {
            println!("called `my::nested::private_function()`");
        }
    }

    mod inaccassible {
        #[allow(dead_code)]
        pub fn public_function() {
            println!("called `my::inaccassible::public_function()");
        }
    }
}

fn main() {
    function();
    my::function();
    // my::private_function(); FIXME: can't access private function
    my::indirect_access();
    my::nested::function();
    // my::nested::private_function(); FIXME: can't access priv. function
    // my::inaccassible::public_function(); FIXME: can't access priv. module
}
