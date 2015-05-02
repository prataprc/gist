fn function() {
    println!("called `function()`");
}

mod my {
    pub fn indirect_call() {
        // access all the functions named `function` from this scope.

        function(); // my::function()
        cool::function(); // my::cool::function()
        { print!("> "); cool::function(); } // my::cool::function()
        { use cool::function; print!("> "); function(); } // cool::function()
        { print!("> "); self::cool::function(); } // my::cool::function()
        { print!("> "); super::function(); } // function()
    }

    fn function() {
        println!("called `my::function()`");
    }
    mod cool {
        pub fn function() {
            println!("called `my::cool::function()`");
        }
    }
}

mod cool {
    pub fn function() {
        println!("called `cool::function()`");
    }
}

fn main() {
    my::indirect_call();
}
