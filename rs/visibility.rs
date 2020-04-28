pub mod doc {
    use super::*;

    pub struct Document {
        pub(crate) typ: String, // only `type` field is exposed.
        id: String,
        key: Vec<u8>,
        val: Vec<u8>,
    }

    impl Document {
        pub fn new(store: &db::Database, key: Vec<u8>, val: Vec<u8>) -> Option<Document> {
            if store.is_lsm {
                Some(Document {
                    typ: Default::default(),
                    id: Default::default(),
                    key,
                    val,
                })
            } else {
                None
            }
        }
    }
}

pub mod db {
    use super::*;

    pub struct Database {
        pub(crate) is_lsm: bool,
        name: String,
    }

    impl Database {
        fn new_doc(&self, key: Vec<u8>, val: Vec<u8>) -> Option<doc::Document> {
            doc::Document::new(self, key, val)
        }
    }
}

fn main() {
    println!("hello world")
}
