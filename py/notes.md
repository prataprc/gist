# BUILT-IN s #

# keywords and constructs

    .
    [,,,] (,,,) {:,:,:}
    * / // + -
    >> <<

    global      for in      in
    del         while       if 
                break       elif 
                continue    else 
                pass        def

# data types

Basic data types are,
    int, long
    float, 
    complex (obj.real, obj.imag), 
    strings, tuples
    list
    dictionaries
    set
    function objects (yes, functions are also treated as objects)
    method objects (function instances of a class-object)
    type (returned by the function type(obj))

# Note:
    There is no seperate character data type. A character is a string of 
    size one.

    # built-in names of different basic data types

    number type,
        _
        None

    string type,
        "__doc__" (module, function, class)

    function type,
        __init__()

    # operations

    On numbers,
    
    On strings,
       +, *

    On sequence types,
        sequence + sequence

    On list types,
        *arg  (unpacking elements into arguments)

    On dictionary types,
        **dict (unpacking keyword into arguments) 

    On set types
        - | & ^

    # Note
        - supports multiple assignments eg, a,b = 0,1
        - the right hand side of the expression is evaluated first 
          (left to right)

    # function operations

    On string type,
        str.strip()

    On list type,
        list.append (item)
        list.remove (item)
        list.extend (list)
        list.instert (offset, item)
        list.index (item)
        list.count (item)
        list.sort ()
        list.reverse ()

    On dictionary type,
        dict.keys()     returns a list
        dict.sort()
        dict.has_key(key)

# functions

len (sequence)
int (obj)
float (obj)
complex (float, float)
type (obj)
range ([start,] stop [,step])
set(list)                       returns a set
dict(tuple_list)                returns a dictionary

filter (function, sequence)     returns a sequence for, function(item) true
map (function, sequence)        returns a sequence with results, function(item)
reduce (function, sequence [,init])     returns a single value

input(str)
raw_input(str)
print ...

execfile("filename.py")

# modules
sys
    [argv]
    "ps1"
    "ps2"

__main__
keyword
sitecustomize
operator

# exceptions

# OBJECTS #

    Objects can be of basic type or of user defined. User defined objects
can be instantiated using class definitions

Aliasing of objects,
    mapping multiple names to a object instance. Something similar to 
pointers, but machine independant.

# operations on non-builtin objects

    obj.<attribute> , where attribute can be data or method names.

# FUNCTIONS

    - Functions are also objects.
    - Parameters can be passed by values or passed by reference
    - Supports default argument value, non-default arguments cannot follow 
      default arguments.
    - Supports keyword arguments, non-keyword argument cannot follow a keyword
      argument.

    - If *name is defined in the formal argument list, then it receives a tuple
      containing the positional arguments beyond the formal parameter list.
    - If **name is define in the formal argument list, then it receives a
      dictionary containing all the keyword arguments.

# NAMESPACE AND SCOPE #

What is a namespace ?
    Namespace is the mapping of the names to objects. And most namespace are
implemented as dictionaries.
    All the assignments are name-to-object binding.

What are scopes ?
    The life time of a namespace

Namespaces are,
    built-in namespace                  __builtin__
    built-in exception names
    global names in a module            __modname__
    local names in a class
    local names in a function
    (attributes)

The hierarchy of namespace,
    function local -> module global -> builtin
    name              modname.name     

The different scopes are,
    The built-in namespace exists for the lifetime of interpreter
    __main__ namespace exists for the lifetime of the interpreter
    local namespace exists until the function returns

    global names (mapped to module containing the class) for 
        class_object.methods

# Note:
    As of now, the name binding and name resolution is done as a runtime 
search (except for the names in the local namespace). But the language 
definition is evolving towards the static binding.


# attributes

What are attributes ?
    any name following a '.', EG: z.real, z.imag, modname.funcname
    EG,
        namespace of a module (objects and functions)
        namespace of a class (objects and functions)
        namespace of a function

Data attributes spring into existence once a value is assigned to it,
     x.counter, where counter need not be previously available in x.

Operations that can be performes on attributes are,
    del modname.funcname

# MODULES

The top level execution of the statements (either through the scripts or 
interactively are part of the module __main__

