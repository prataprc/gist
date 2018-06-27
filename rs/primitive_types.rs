char        A character type.
f32         The 32-bit floating point type.
f64         The 64-bit floating point type.
unit        The () type, sometimes called "unit" or "nil".

fn          Function pointers, like fn(usize) -> bool.
never       The ! type, also called "never".
pointer     Raw, unsafe pointers, *const T, and *mut T.
reference	References, both shared and mutable.

array       A fixed-size array, denoted [T; N], for the element
            type, T, and the non-negative compile-time constant size, N.
slice	    A dynamically-sized view into a contiguous sequence, [T].
str	        String slices.
tuple	    A finite heterogeneous sequence, (T, U, ..).

i8,i16,i32,i64,i128,isize
-------------------------

from_str_radix, pow, abs, signum, is_positive, is_negative,
reverse_bits, swap_bytes,
min/max_value, count/trailing/leading_ones/zeros,
rotate_left/right, from/to_be/le

checked_add/sub/mul/div/rem/neg/shl/shr/abs/pow
saturating_add/sub/mul/pow
wrapped_add/sub/mul/div/rem/neg/shl/shr/abs/pow
overflowing_add/sub/mul/div/rem/neg/shl/shr/abs/pow

u16,u32,u64,u128,usize
-------------------------

from_str_radix, pow, is/next_power_of_two,
reverse_bits, swap_bytes,
min/max_value, count/trailing/leading_ones/zeros,
rotate_left/right, from/to_be/le

checked_add/sub/mul/div/rem/neg/shl/shr/abs/pow
saturating_add/sub/mul/pow
wrapped_add/sub/mul/div/rem/neg/shl/shr/abs/pow
overflowing_add/sub/mul/div/rem/neg/shl/shr/abs/pow

u8 (additional)
---------------

is_ascii, eq_ignore_ascii_case,
is_ascii_alphabetic/uppercase/lowercase/alphanumeric/digit/
is_ascii_hexdigit/punctuation/graphic/whitespace/control,
to_ascii_uppercase/lowercase, make_ascii_uppercase/lowercase,

bool
----
