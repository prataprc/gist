fn main() {
}

pub fn into_string(self: Box<str>) -> String {
    let slice = Box::<[u8]>::from(self);
    unsafe { String::from_utf8_unchecked(slice.into_vec()) }
}
