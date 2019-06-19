// type describing its capabilities.
trait Capabilities {
    fn name(&self) -> String;
    fn capable_of(&self) -> Vec<String>;
    fn new_trait1(&self) -> Option<Box<dyn Trait1>>;
    fn new_trait2(&self) -> Option<Box<dyn Trait2>>;
}

trait Module {
    fn get_module_info() -> ModuleInfo;
    fn module_init() -> i32;
    fn module_cleanup();
    // return a vector of capability objects, each object shall
    // describe a type implementing one or more capabilities.
    fn capabilities(&self) -> Vec<Box<dyn Capabilities>>;
}

trait Trait1 {
    fn handle1(&self, a: i32) -> String;
}

trait Trait2 {
    fn handle2(&self, a: i32) -> String;
}

struct A {
    data: i32,
}

impl Trait1 for A {
    fn handle1(&self, a: i32) -> String {
        format!("{}", self.data + a)
    }
}

impl Trait2 for A {
    fn handle2(&self, a: i32) -> String {
        format!("{}", self.data + a)
    }
}

impl Capabilities for A {
    fn name(&self) -> String {
        "a".to_string()
    }

    fn capable_of(&self) -> Vec<String> {
        vec!["trait1".to_string(), "trait2".to_string()]
    }

    fn new_trait1(&self) -> Option<Box<dyn Trait1>> {
        Some(Box::new(A { data: 100 }))
    }

    fn new_trait2(&self) -> Option<Box<dyn Trait2>> {
        Some(Box::new(A { data: 200 }))
    }
}

struct B {
    data: i32,
}

impl Trait1 for B {
    fn handle1(&self, a: i32) -> String {
        format!("{}", self.data + a)
    }
}

impl Capabilities for B {
    fn name(&self) -> String {
        "a".to_string()
    }

    fn capable_of(&self) -> Vec<String> {
        vec!["trait1".to_string()]
    }

    fn new_trait1(&self) -> Option<Box<dyn Trait1>> {
        Some(Box::new(B { data: 1000 }))
    }

    fn new_trait2(&self) -> Option<Box<dyn Trait2>> {
        None
    }
}

struct Mod;

impl Module for Mod {
    fn capabilities(&self) -> Vec<Box<dyn Capabilities>> {
        let mut res: Vec<Box<dyn Capabilities>> = vec![];
        res.push(Box::new(A { data: 10 }));
        res.push(Box::new(B { data: 10 }));
        res
    }
}

fn main() {
    let m = Mod;
    let meta = m.capabilities();
    println!("{}", meta.len());
}
