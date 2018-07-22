What Go ?
---------

* A new language from Bell labs and Google.

* Concurrent programming

* Garbage-collected

* Machine compiled

* Systems programming

Go Goals !
----------

Golang aims at following goals.

* Efficiency of a statically-typed compiled language
  with the ease of programming of a dynamic language.

* Safety: type-safe and memory-safe.

* Good support for concurrency and communication.

* Fast compilation time.

How to Goals ?
--------------

How go aims to achieve these goals ?

* Efficiency of a statically-typed compiled language
  with the ease of programming of a dynamic language.

Sticks to the conventional and traditional syntax of curly
braced languages and manages to include only those language
concepts used by most of the programmers, most of the time.

This combined with some clever syntax makes it quick-to-learn
language, while keeping the programmer as productive as Python.

* Safety: type-safe

No warning and only errors. No crazy type coersion rules.
And no pointers arithmetic.

* Safety: memory-safe

No segmentation fault, no memory leaks - only garbage collection.
But, hey you can do your own memory allocation as well.

* Good support for concurrency and communication.

Do not communicate by sharing memory; instead, share memory by
communicating.

Communication through channels, channels are typed and channels
are first class citizens.

Where to use Go ?
-----------------

* Quick prototyping -
  every growing library, shipped with the language.

* Easier for network / socket programming. TBD

* Utilize multi-core CPUs.

* To build a cluster of services.

* Cross platform.

Compiletime
-----------

* Clean, concise syntax.

* Lightweight type system.

* No implicit type conversions.

* Strict separation of interface and implementation.

Runtime
-------

* Garbage collection.

* Strings, Maps, Channels.

* Concurrency and Scheduler.

Packaging
---------

* Explicit dependencies to enable faster builds.

* Import from github or other repository sources.

* No DLLs or dynamically liked libraries. Atleast not for now.

Concurrency
-----------

* Programs spawn goroutines, and routines shall return to exit.

* Runtime spawn one ore more threads to execute go-routines.

* Scheduler to multiplex go-routines onto OS threads.

Concurrency is hard without garbage collection, garbage collection
is hard without the right language.

Types
-----

Go type system is almost as simple as C but can be much more
useful by enforcing strict rules when operating on typed data.

* Reduce finger typing

* Stay away from heirarcy of types. According to golang creaters !

  "Types in large programs do not easily fall into hierarchies.
  Programmers spend too much time deciding tree structure and
  rearranging inheritance."

Hello World
-----------

package main

import "fmt"

func main() {
    fmt.Printf("hello world\n")
}

Program Execution
-----------------

TBD: main() , init() ?
TBD: Order of calling Init() ?

Golang talks
------------

https://talks.golang.org/2009/go_talk-20091030.pdf
