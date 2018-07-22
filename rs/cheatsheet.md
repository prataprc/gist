Types
-----

i8, i16, i32, i64, i128, u8, u16, u32, u64, u128, isize, usize
f32, f64, char, bool

```
[T; N], [T], str, tuple, fn
&T, &mut T, *const T, *mut T, !, ()
```


Box<T>, Rc<T> Arc<T>, Cow<'a, T>
Vec<T>, String, CString, CStr
OsString, OsStr, PathBuf, Path
TypeId,
Ordering, Reverse<T>
Range<Idx>, RangeInclusive<Idx>, RangeFull
RangeTo<Idx>, RangeFrom<idx>, RangeToInclusive<idx>

Operators
---------

```
+ - * / % += -= *= /= %= -()
& | ^ >> << &= |= ^= >>= <<=
* [] , -> . ; => @ | _ ? !
== != < <= > >= !
&& ||
.. expr..expr ..expr expr.. expr..=expr ..=expr
expr...expr
var = expr, ident = type
&expr &mut expr
&type, &'a type, &mut type, &'a mut type
*const type, *mut type
trait + trait, 'a + trait
pat: type, ident: type, ident: expr, 'a: loop {}
```

macro!{} macro![] macro!()
'ident, "...", r"...", r#"..."#, r##"..."##
b"...", br"...", br#"..."#, br##"..."##

Traits
------

Clone, Any, Default, Error,
Borrow<T>, BorrowMut<T>, ToOwned{type Owned}
From<T>, Into<T>, AsRef<T>, AsMut<T>

Iterator{type Item}, DoubleEndedIterator,
IntoIterator{type Item; type IntoIter}, FusedIterator, ExactSizeIterator,
Sum<A=Self>, Product<A=Self>, FromIterator<A>, Extend<A>

Debug, Display

PartialEq<T>, Eq, PartialOrd<T>, Ord, Not{type Output}
FnOnce<Args>{type Output}, FnMut<Args>: FnOnce<Args>, Fn<Args>: FnMut<Args>
Index<Idx>{type Output}, IndexMut<Idx>{type Output}
Try{type Ok, type Error}

Add<RHS=Self>{type Output}, AddAssign<Rhs=Self>
Sub<RHS=Self>{type Output}, SubAssign<Rhs=Self>
Div<RHS=Self>{type Output}, DivAssign<Rhs=Self>
Mul<RHS=Self>{type Output}, MulAssign<Rhs=Self>
Rem<RHS=Self>{type Output}, RemAssign<Rhs=Self>
Net{type Output},
BitAnd<RHS=Self>{type Output}, BitAndAssign<Rhs=Self>
BitOr<RHS=Self>{type Output}, BitOrAssign<Rhs=Self>
BitXor<RHS=Self>{type Output}, BitXorAssign<Rhs=Self>
Shl<RHS=Self>{type Output}, ShlAssign<Rhs=Self>
Shr<RHS=Self>{type Output}, ShrAssign<Rhs=Self>

Dref{type Target}, DrefMut

Hash

Sized, ?Sized, Copy, Send, Sync
Drop

Jargons
-------

crates
items and attributes
modules
linkage
macros
bringing into scope
implement structure
implement a trait for structure
contant items
static items
inlining
traits and trait implementation syntax
scalar types and composite types
tuple and array
slices
types aliases, associated types.
structure
enumerations and unions
functions, function-pointer, extern-functions, extern-blocks
types of function calls - FnOnce, Fn, FnMut
type parameters
Copy and Clone
Move and Drop
ownership, borrow, reference
mutable reference and immutable reference
lifetimes and lifetime elision
higher ranked types for lifetime

variable bindings
zero-sized value - function-item, tuple-struct, enum-variant
tail expression, divergent-expression, divergent-functions
trait bounds, where clause and widening bounds.
trailing path component - ``mem::size_of::<u32>()``
primitive casting (as)
labeled loops
constant items (functions and vars)
structure update

Identifier rule:
----------------

* crate-names, module-names, use-as-names,
  constant-vars static-vars,
  fn-names, type-names, struct-names, enum-names, trait-names, union-names
  vars, lifetime, label
* an identifier is [a-zA-Z][a-zA-Z0-9_]\*.

Type parameter rule:
--------------------

* Functions, type aliases, structs, enumerations, unions, traits and
  implementations may be parameterized by type.
* The type parameters of an item are considered "part of the name",
  not part of the type of the item.
* There are no general type-parametric types, only type-parametric items.
  That is, Rust has no notion of type abstraction: there are no
  higher-ranked (or "forall") types abstracted over other types,
  though higher-ranked types do exist for lifetimes.
* When types are bounded by traits:
  There is a case called widening bound; in general bounds impose more
  constraints, but in the case of ``Sized`` it was decided that unless
  otherwise noted a generic T would be assumed to be Sized. The way to
  note the opposite would be to mark it ``?Sized`` ("maybe Sized").

Copy, Drop, Clone and move semantics:
-------------------------------------

* Copy is primitive trait representing basic property of types.
* Copy simply copy bits and fast. And cannot be overloaded for a type.
* By default variable bindings have move semantics.
* Clone is super-traite of Copy.
* Copy cannot be derived for a type without deriving Clone.
* Move semantics can be overriden by deriving Copy,Clone.
* Any type implementing Drop cannot Copy, because it's managing
  some resource besides its own size_of::<T> bytes.

Copy Implementors:
------------------

* Immutable reference implement Copy.
* Mutable reference do not implement Copy.
* Function item types (i.e. the distinct types defined for each function).
* Function pointer types (e.g. fn() -> i32)
* Array types, for all sizes, if the item type also implements Copy
  (e.g. [i32; 123456]).
* Tuple types, if each component also implements Copy
  (e.g. (), (i32, bool))
* Closure types, if they capture no value from the environment or if all
  such captured values implement Copy themselves.

Memory rules:
-------------

* Sizeof types are dependant on the type-layout representation -
  C, default-representation, primitive-representation, packed.

Function traits:
----------------

* Function item types, tuple-struct and enum variant are zero-sized values,
  no indirection is needed when the function is called.
* All function items implement ``FnOnce``, ``Fn``, ``FnMut``,
  ``Copy``, ``Clone``, ``Send``, and ``Sync``.
* As with let bindings, function arguments are irrefutable patterns.
* Every control path in a function ends either with a `return` or,
  `tail-expression` or `divergent-expression`.

Privacy Rules:
--------------

Overall, these are the rules for item visibility:

* If an item is public, it can be accessed through any of its parent
  modules.
* If an item is private, it can be accessed only by its immediate parent
  module and any of the parent’s child modules.

Bootstraping
------------
beta{std,rustc,cargo}
    bootstrap (local source-base)
    build_helper (local source-base)
    cc, cfg-if, cmake, dtoa, filetime, fixedbitset, getopts,
    itoa, lazy_static, libc, num_cpus, num-traits, ordermap,
    petgraph, proc-macro2, quote, serde_derive_internals, serde_derive,
    serde_json, serde, syn, time, toml, unicode-xid
Stage0{std,test,rustc,codegen} compiling, codegen{LLVM module for target}.
Assembling Stage1 compiler
Stage1{std,test,rustc,codegen} compiling using State1 toolchain
Assembling Stage2 compiler
Stage2{std,test,rustc} Uplifting from Stage1
Stage2{rust-doc}
