1. Operators :

  Arithmetic, Bitwise, logical : 

    + - * / ADD, SUB, MULT, DIV
    %       MOD
    **      EXP

    &   AND
    |   OR
    ^   XOR (Exclusive)
    ~   ONE's COMPLEMENT
    <<  arithmetic LEFT SHIFT
    >>  arithmetic RIGHT SHIFT

    && and
    || or
    !  not


  All the above operators are binary operators (except unary-minus and logical
  not) and are implemented as object methods.
    
  Assignment : 

    =
    a, b = 10, 20  (parallel assignment)

    += -= *= /= %= **=
    &= |= ^= <<= >>=
    &&= ||= !=

  Assignments are also treated as expressions. Atleast syntactically !!

  For Parallel assignments, if more variables are specified to the left than
  there are values on the right of an assignment, any trailing variables will
  be assigned nil.

  Comparison : 

    == != > < >= <=
    <=>                 'Combined Comparison', returns 0 or 1 or -1
    ===                 Membership operator
    ==                  Check for same `object_id` (default, Kernel)
    .equal?             Check for `object_id` equality (similar to `==`)
    .eql?               Check for both type and value equality

  * All comparison operator except 'Combined Comparison' returns boolean
    'true' or 'false'
  * '===' operator is defined in `Object` class which is normally overriden in
    derived class like `Range`. This operator is especially useful for `case`
    statement.
        Eg, (1..10) === 5, Range object here receives the membership message.
  * To check for identical `object_id` use `equal?` instead of '==' since it
    could be overriden by the derived class.

  Range, Index, Array : 

  [a,b,...] Array
  [a]       Array index
  [off,cnt] Splice array for <cnt> elements from <off> 

  m..n      Inclusive range from offset m to n, where m < n
  m...n     Exclusive range from offset m to n, where m < n

  Negative offset is allowed where by -1 denotes the last element.

  Indirection : 

  .    
    Class.methodname
    object.methodname
    Module.methodname
    Scope resolution operator for objects and classes
  ::
    Class::Constant 
    Class::Class
    Class::Class::Constant
    Module::Constant 
    Module::Class
    Module::Class::Constant
    ::<name>
    Scope resolution operator for Constant names, Class names and Module names 
    in classes and modules.

  Miscellaneous : 

  =>    Hash key,value seperator
  ,     Array / Hash element seperator
  ?:    Ternary operator
  <derived-class> < <base-class>
        class Class < BaseClass.
  def <method>=
        def methodname=(RHS_value).
  = <<<end-marker>
  <text>
        HEREDOCS, to write multiline string with delimiter. Text must be flush
        with spaces on the left side, to indent `text`, the endmarker must be
        preceded by <<- instead of a <<. By default, HEREDOCS are treated as
        double quoted string, to force it as single-quoted string, enclose the
        end-marker within single-quotes.
  class << <obj-instance>
        Extend an object using a singleton class definition.

  true
    TrueClass instance.
  false
    FalseClass instance.

  Operator overloading method names use the same atom as that of the
  operator.

2. Keywords :

    [Scope]     [Code]      [Control]   [Operation]     [Runtime]

    alias                               and
    BEGIN
    begin
                            break
                            case
                class 
                def
    defined     do
                            else
                            elsif
    END
    end
                            ensure      false
                            for
                            if
                            in
                module      next        nil
                                        not
                                        or
                            redo
                            rescue
                            retry
                            return
                                                        self
                                                        super
                then                    true
    undef                   unless
                            until
                            when
                            while
                yield
                __FILE__
                __LINE__


  self ..... this object.
  nil ...... emitted when referencing undefined symbols. Can also be used to
             denote 'emptiness' or 'undefined'.
  super .... Invoke ancestor class' matching method (instance-method and
             class-method), with arguments.
  true ..... Instance of TrueClass, used in condition checks.
  false .... Instance of FalseClass, used in condition checks.
  __FILE__ . Name of the current source file.
  __LINE__ . Current line number in the file.
  defined .. Whether or not the passed expression is defined.

  Names : 
  
  <local_variable> ................ Local variable
  $<global_variable> .............. globalname start with small letter
  @<instance_variable> ............ variable name starts with small letter
  @@<class_variable> .............. variable name starts with small letter
  <Capitalletter>[Class_name] ..... Class name starts with caps
  <Capitalletter>[constant_name] .. Constant name starts with caps
  <smallletter>[function_name] .... Function name starts with small letter
  <smallletter>[method_name] ...... Method name starts with small letter
  :<symbolname> ................... Refering to symbol object
  <methodname>= ................... Methodname can be used as LHS
  <methodname>! ................... Convention that method creates side-effects

  'instance variable' can be defined inside,
    main-program,    belongs to 'main'
    class,           belongs to the Class object
    module,          belongs to the Module object
    instance-method, belongs to the Class instance
    class-method,    belongs to the Class object
    module-method.   belongs to the Module object
  'class variable' can be defined inside,
    class,
    module,
    instance-method,
    class-method,
    module-method.

    class-variables must be initialized.
    Are class-variables allowed inside modules ???

  Un-initialized instance variables will yield `nil`, while un-initialized
  local variables will throw up error.

  Symbols : 

    :<localvar>, :<@instvar>, :<@@classvar>, :<$globalvar>, :<Constvar>
    :<Class>, :<Module> :<method>

  It is not a string, it is not a constant and it is not a variable. A symbol
  is, quite simply, an identifier with no intrinsic meaning other than its own
  name.

  A symbol is unique, so :hello, :hello and :hello all refer to the same
  object with the same object_id.

  Can be passed as arugments to methods and returned from methods are result.
  It can be used in comparison checks as well.

  The scope in which a symbol is declared does not affect its uniqueness.

  'symbol literals', let us say there is an identifier by name `name`, the
  identifier is stored as a symbol. Actually the notation :<name> is the
  literal way of denoting that symbol. But by itself it does not yield the
  value that the identifier refers to. To refer to the value that `name`
  points to, evaluate :<name> literal and its `id2name` method to fetch the
  value.

        eval( :<symbol>.id2name )

3. Data types :

  'immediate value'
    This means that when they are assigned or passed as parameters, the actual
    object is passed, rather than a reference to that object. Assignment does
    not alias Fixnum objects. There is effectively only one Fixnum object
    instance for any given integer value, so, for example, you cannot add a
    singleton method to a Fixnum.

  Number Literal : 

    Large numbers   (Bignum)
    Native numbers  (Fixnum)
    Integer is the base class for Bignum and Fixnum. Fixnum objects have
    immediate value.

    123                  # Fixnum decimal
    1_6889               # Fixnum decimal with underline
    -5000                # Negative Fixnum
    0377                 # octal
    0xee                 # hexadecimal
    0b1011011            # binary
    ?b                   # character code for 'b'
    ?\n                  # code for a newline (0x0a)
    12345678901234567890 # Bignum

  Floating point literal : 

    1023.4               # floating point value
    1.0e6                # scientific notation
    4E20                 # dot not required
    4e+20                # sign before exponential

  String Literal : 

    Single Quotes :
      Raw character string. Except,
        - A single-quoted string can, however, use a backslash to indicate that
          the next character should be used literally. like,
            > 'hell\'s angle'

    Double Quotes :
      Support escape sequence, and,
      #{} expression evaluation, come, substitution

    User defined Quotes :
      %Q/This is the same as a double-quoted string./
      %Q[This is the same as a double-quoted string.]
      %/This is also same as a double-quoted string./
      %q/And this is the same as a single-quoted string/

    Executing OS command :
      `os-command`
      %x{some command}
      %x/some command/

    Print format :
      %d – decimal number
      %f – floating point number
      %o – octal number
      %p – inspect object
      %s – string
      %x – hexadecimal number

  * String objects are immutable objects, except for few functions that
    generally end with an '!'
  * Since Ruby aims to be a pure OO, there is no difference between built-in
    data types and user defined data types.
  * Operator, + and << means concatenate the two strings that are operands.
        s = "Hello " << "world"
        s = "Hello " +  "world"
        s = "Hello "    "world"

  Array : 

   [ <element>, <element>, ... ]
   same as,
   <element>, <element> ...

   +          operator appends another array.
   <<         operator extends another array.
   <=>        Testing for equality. (Comparable).
   %w( ... )  shortcut to create an array from list of string.

   Comparable class automatically includes methods for comparison operators
   which internally uses the '<=>' method.

  Hash : 

    { <key> => <value>,
      <key> => <value>,
      <key> => <value>,
      ...
    }

  Regular expressions : 
    
    Reg-ex strings are enclosed by /../. // denotes empty string and matches
    every character in the string.
    
  [Type convertion]

4. Statements :

  Though assignments are statements, syntactically it can behave like an
  expression, like,

  Conditional : 

  | if <bool-expr> then
  |     <code>
  | elsif <bool-expr> : <code>
  | else <code>
  | end


  | <expression> if <bool-expr>


  | begin
  |     <code>
  | end if <bool-expr>


  | unless <bool-expr> then
  |     <code>
  | else <code>
  | end


  | <expression> unless <bool-expr>


  | begin
  |     <code>
  | end unless <bool-expr>


  | case <target-expression>
  |     when <comparison> [, comparison] ... : <code>
  |     else <code>
  | end

  Brackets are optional.

  Case statement 'when' keyword uses membership operator when more than one
  comparison is used (seperated by comma or generated by range-operator). This
  can be used as a shorthand form of if...elsif...else

  There is no need for 'break' statement in the <code> block since upon match
  the execution will execute the corresponding <code> and exit the case
  statement.

  Case statment can be used as expression, by omitting the <expression> part.

  Looping : 

  * Iterator
  | for <LHS> in <iterable> do
  |     <code>
  | end


  | while <bool-expr> do
  |     <code>
  | end

  * Single-line `while` modifier
  | <expression> while <bool-expr>

  * Multi-line `while` modifier
  | begin
  |     <code>
  | end while <bool-expr>


  | until <bool-expr> do
  |     <code>
  | end

  * Single-line `until` modifier
  | <expression> until <bool-expr>

  * Multi-line `until` modifier
  | begin
  |     <code>
  | end until <bool-expr>

  * Infinite looping
  | loop do
  |     <code-block>
  |     ... break ...
  | end


  In begin .. end syntax the code block executes atleast once, even if
  <condition> fails.

  When using 'loop' method make sure that the code exits using 'break'

  'break', terminates loop immediately.
  'redo',  immediately repeats w/o rerunning the condition.
  'next',  starts the next iteration through the loop.
  'retry', restarts the loop, rerunning the condition

  Exception : 

    begin
        <code>
    rescue <Exception Class>, <Exception Class> => <exc>
        <code>
        raise
    rescue <Exception Class>, <Exception Class> => <exc>
        <code>
        retry
    else 
        <code>
    ensure
        <code>
    end

  $! is a global variable containing the last exception object.

  Alternately, <exc> specifies exception object.

  Object class is the ultimate ancestor of all exceptions. By trapping on
  Object, it is possible to catch all exceptions.

            Object
              ^
              |
           Exception
              ^
              |
         StandardError
              ^
              |
        OtherExceptions

  When handling multiple exception types you should always put the rescue
  clauses dealing with specific exceptions first, then follow these with
  rescue clauses dealing with more generalized exceptions.

  Code block after 'ensure' is always executed.

  Code block after 'else' is executed only when exception has not occured.

  If you think an error condition may be transient or may be corrected (by the
  user, perhaps?), you can rerun all the code in a 'begin..end' block
  using the keyword 'retry'

  Sometimes you may want to keep an exception `alive` even after it has been
  trapped in an exception-handling block. This can be used, for example, to
  defer the handling of the exception - say, by passing it on to some other
  method. You can do this using the 'raise method'.

        raise                       # Raises RuntimeError or $! exception
        raise "error message"
        raise ZeroDivisionError
        raise ZeroDivisionError.new("error message")

  You may optionally omit 'begin' and 'end' when trapping exceptions inside a
  method, a class or a module

  BEGIN statement : 

  Declares code to be called before the program is run.

          BEGIN {
                 <code>
          }

  END statement : 

  Declares code to be called at the end of the program.

          END {
                 <code>
          }

5. Code :

  Code Block : 

    <method> {
       <code-block>
    }

    <method> do
        <code-block>
    end

  Code blocks are 'anonymous functions', and are always associated with a
  method call.

  Variables between the vertical bars are call 'Block parameters'. Block
  variables themselves have no `existence` outside the block.

  Code blocks are not objects. This is a great exception to Ruby's obsessive
  OO design.

  It is also possible to create standalone code blocks as code objects.

    a = Proc.new { |x| x = x*10; puts(x) }
    b = lambda { |x| x = x*10; puts(x) }
    c = proc { |x| x.capitalize! }

  In the above case, all a, b, c are instance of Proc class. To execute the
  code, use the call() method

    a.call( arg1, ... )
    b.call( arg1, ... )
    c.call( arg1, ... )

  One difference between a and b,c is that 'Proc.new' does not check that the
  number or arguments passed to the block match the number of block
  parameters. But 'proc' and 'lambda' do. Both proc and lambda are methods,
  not keywords.

  'scope', variable scope is a curious thing with block. The code-block always
  uses the local variables in the scope in which it is `defined` and instance
  variables of the object in which the block is `defined`.

  'Closure', is the name given to a function which has the ability
  to store (that is, to `enclose`) values of local variables within the scope
  in which the block was created (think of this as the block’s `native scope`).
  And the block is able to carry that variable into a different scope.
  Using one of the ways to instantiate a code-block object, it is also
  possible for a method to return nameless code-block.

  'yield', is closely associated with code-blocks. When ever a code block is
  associated with a method, it can yield to the code block passing it
  parameters and continue from yield once the code-block returns.

  Code blocks when associated with a method is implicitly passed to the method
  at the end of the formal parameter list. Methods can access its code-block
  using the following syntax.
        
        def method( arg1, arg2, arg3, &code )
            <code>
        end

  Here &code refers to the associated code-block as 'Proc' object. And when
  used this way, method call is type-checked with the function signature.

  Code-blocks can be nested, like, 

        ["hello","good day","how do you do"].each {
            |s| caps( s ){
                |x|
                x.capitalize! 
                puts( x )
            }
        }

  Precedence,
        foo bar do |s| puts( s ) end
        foo bar{ |s| puts(s) }
  Here, foo and bar are methods. So to which method is the block passed ? It
  turns out that the do..end block would be passed to the leftmost method,
  `foo`, whereas the block in curly braces would be sent to the rightmost
  method, `bar`. This is because curly braces are said to have higher
  precedence.

  If a block may truly be regarded as a nameless function or method then,
  logically, it should be able
    1) to contain its own local variables and
    2) to have access to the instance variables of the object to which the block
       belongs.

  Pitfall,
  Now, in principle, block parameters should be visible only within the block
  itself. However, it turns out that assignment to block parameters can
  initialize the values of any local variables with the same name within the
  block’s native scope. Expected to change in Ruby 2.0.

  Arguments and return values : 

  All methods always return a value though you are not, of course, obliged to
  use it. When no return value is specified, Ruby methods return the result
  of the last expression evaluated. When nothing is evaluated, 'nil' is
  returned.

  Ruby is capable of returning multiple values all in one go. And the
  collection of returned values will be treated as 'Array'. It is also possible
  to explicitly return a different collection object, like Hash.

  All parameters are positional parameters. There are no keyword arguments
  like in Python. But on the other hand, default values can be assigned in
  the parameter list of a method using the usual assignment operator.

        def aMethod( a=10, b=20 )
            return a, b
        end

  Variable number arguments can be received as,

        def aMethod( a=10, b=20, c=100, *d )
            return a, b, c, d
        end


6. Class :

  Everything is an object, even the class that defines an object is an object.
  And all operations done with an object is done by a method, the only
  exception to this rule is the '=' operation.

  Following can be defined inside a class,
        constants, instance methods, class methods, classes,
        instance-variable, class-variables, local-variables.

  Apart from this instant-methods can define instance-variables pertaining to
  the instance-object.

  'Partial class definition'
    Single class can be defined in multiple places in bits and pieces. Every
    partial definition must exactly match the ancestor class, if defined.
    When instantiating an object of a particular class (say, Cls) all the partial
    definitions of that class (Cls) interpreted so far (including its ancestor
    classes) will be accounted for.

  Standard classes : 

                           +------------------------------+
                           |                              |
      BasicObject --> (BasicObject)                       |
           ^                ^                             |
           |                |                             |
         Object ------> (Object)                          |
          ^  ^            ^  ^                            |
          |  |            |  |                            |
          |  |            |  +-------------------+        |
          |  +------------|----------+           |        |
          |               |          |           |        |
          |               |        Module ---> (Module)   |
          |               |          ^            ^       |
          |               |          |            |       |
      OtherClass --> (OtherClass)    |            |       |
                                   Class ---->  (Class)   |
                                      ^                   |
                                      |                   |
                                      +-------------------+
    
  'new'
    class-method of 'Object' Class, used to instantiate a new object.

  'initialize'
    method that will be called when ever <Class>.new constructor is called.

  'super'
    super is a keyword which acts like a function to call base-class methods
    (instance-methods / module-methods / class-methods)
        super               # call base class method with all arguments passed
        super()             # call base class method with no arguments
        super(arg1, agr2 )  # call base class method with arg1 & arg2 arguments

  Accessor Methods : 

    - methoname appended with '='
    - attr_reader( symbols )
    - attr_writer( symbols )
    - attr_accessor( symbols )

  The accessor methods automatically create accessor methods to access
  instance variables, although the instance variable itself will be created
  when writing it (for the first time).

  It is possible to use accessor methods inside module definition.

  Instance methods : 

  An instance method belongs to a specific instance of a class – in other
  words, to an individual object. A Class cannot call its instance-method.

  Class methods : 

  A class method belongs to the class itself. In order to define a class
  method you may precede the method name with the class name and a full stop.
  Instances of a Class cannot call its class-methods.

        def Classname.<class_methodname>    # Define
        end

        Classname.<class_methodname>()      # Call

  Classes can also have instance-variable which are accessible only by
  class-methods. Whereas, class-variables are accessible to both class methods
  and instance methods.
  On the other hand, instance-variable defined inside instance-methods are
  accessible only in the context of instance-object.

  Singleton-methods : 

  A singleton method is a method which belong to a single object rather than
  to an entire class.

    defining singleton-method for object,
        def <objectname>.<methodname>
        end

    alternately,
        class << <objectname>
            def methodB
                puts("b")
            end
            def methodC
                puts("c")
            end
        end

  Now, some classes also have class methods, that is, methods which belong to
  the Class object itself. In that sense these are singleton methods of the
  Class object.

    defining singleton-method for Class,
        def <Classname>.<methodname>
        end

    alternately,
        class MyClass
            class << self
                def methodB
                    puts("b")
                end
                def methodC
                    puts("c")
                end
            end
        end

  Singleton-class : 

  A singleton class, on the other hand, is a class which defines a single
  object.

    ob = Object.new
    class << ob
        def ...(aStr)
            <code>
        end
    end

  Overriding methods : 

  When a method in one class replaces a method of the same name in an ancestor
  class, it is said to 'override' that method.

  Public methods : 

  Default. Accessible by all external code.

  Private methods : 

  Accessible only by instance method and class method defined inside a class.
  This can be worked around by,

        ob.send( :<private_methodname>, arg1, arg2, ... )

  Protected methods : 

  In addition to being visible to the methods of the current object, a
  protected method is also visible to objects of the same type when the second
  object is within the scope of the first object.

  'public', 'private' and 'protected' are not keywords. They are methods of
  Module class.

  Nested methods : 

  You can nest methods (have one method nested inside another).
  So, for example, if method x needs to do calculation y at several different
  points, you can put the y method inside the x method.

  Nested methods are not initially visible outside of the scope in which they
  are defined. While y and z may be called from inside x, they may not be
  called by any other code.

  However, when you run a method that encloses nested methods, those nested
  methods will be brought into scope outside that method!

  Behavioural-core-libraries : 

    (Classes)
    BasicObject, Binding, Class, Continuation, Data, Delegator,
    Enumerator, Exception, Forwardable, Interrupt, Method, Module, Object,
    Observable, Proc, Range, Symbol, UnboundMethod

    (Modules)
    Comparable, Enumerable, FileTest, GC, Kernel, Math, ObjectSpace,
    Precision, Process, Signal

  Core-libraries : 

    BigDecimal, Bignum, Benchmark, ConditionVariable, Coverage, Date, DateTime,
    FalseClass, Fiber, Fixnum, Float, Hash, IO, Integer, Logger, Marshal,
    Matrix, MatchData, Monitor, Mutex, NilClass, Numeric, OpenStruct, PStore,
    RegExp, Set, SimpleDelegator, SingleForwardable, SortedSet, String,
    Thread, Time, Timeout, Tracer, TrueClass, Vector, 

  Some of the above libraries are Modules, and not Classes.

  Methods of Kernel class are automatically available to the programs.


7. Modules :

  A module is also an object. Each named module is an instance of Module
  class.
            module MyMod
            end

  Following can be defined inside a class,
        constants, instance methods, module methods, classes,
        instance-variable, class-variables, local-variables.

  'instansiation' and 'inheritance' are not supported by module. Module class
  itself has a superclass, Object. However, any named module defined by the
  program do not have any super-class.

  The definition of a module looks very similar to a class. In fact, Modules and
  classes are closely related - the Module class is the immediate ancestor of
  the Class class. Two reasons, why `modules` exists are 'namespaces' and
  'mixins'.

  'include', as the module defines a closed namespace, any code outside the
  module won't be able to see the instance method inside the module. That is
  why Ruby explicitly defines Mixins.
    
            include <Module_name>
  
  inside a class, it will import all the instance methods defined inside a
  module as if they are instance methods defined inside the class itself.

  'extend' is commonly used to mix instance methods of a module into a class.

  When you mix modules into a class definition, any objects created from that
  class will be able to use the instance methods of the mixed-in module just
  as though they were defined in the class itself.

  Note, incidentally, that any variables which are local variables in the
  module cannot be accessed from outside the module. This is the case even if
  a method inside the module tries to access a local variable and that method
  is invoked by code from outside the module.

  A module may have its own instance variables which belong exclusively to the
  module object. These instance variables will be in scope to a module-method.

  But instance variables that are referenced in instance objects belong to
  the scope into which that module is included.

        module X
            @instvar = "X's @instvar"
            def amethod 
                @instvar = 10       # creates @instvar in current scope
                puts(@instvar)
            end
        end

  Class variables are also mixed in and, like instance variables, their values
  may be reassigned within the current scope,
  
        module X
            @@classvar = "X's @@classvar"
        end

        include X
        puts( @@classvar )      #=> X's @classvar
        @@classvar = "bye bye"
        puts( @@classvar )      #=> "bye bye"

  'name-conflicts', While mixin-in name-conflicts can occurs between module's
  instance methods defined with the same name, this does not happen with
  module-methods. One way to work-around such conflicts is by using 'alias'.
        alias aliasedname definedname

  'require' is a method that can load external script files. Returns true if
  successful. Any code which would normally be executed when a file is run
  will be executed when that file is required. And namesspace of the required
  file will be merged with the main namespace.

  'load' is a method that is similar to `require`. Except, load can take an
  optional second parameter which, if this is true, loads and executes the
  code as an unnamed or anonymous module. The file loaded does not introduce
  the new namespace into the main program.

  'autoload', works in a similar way to require, but it only loads the file
  specified when a constant of your choosing is accessed / used for the first
  time.

  Another difference is that `require` loads a file once only (even if your code
  requires that file many times) whereas `load` causes the specified file to be
  re-loaded each time load is called.

  'module_function', if you want a function to be available both as an
  instance and a module-method, you can use the method `module_function` with
  a symbol matching the name of an instance method.

  'extend', You can add the methods of a module to a specific object (rather than to an
  entire class) using the `extend` method

          ob = MyClass.new  # Instance of class MyClass
          ob.mymethod       # instance-method in MyClass
          ob.extend(A)      # Extend the object with instance-method of module A

  When an object is extended with a module containing a method with the same
  name as a method in the object’s class, the method from the module replaces
  the method from the class.

8. Runtime :

  Methods : 
    puts, print, gets, defined?

  Scope : 

    'main'
      object instance of class 'Object' that encapsulates all the
      free-standing bits of code (and functions) inside a script file.

    'instance variable'
      Available only to the instance method of object, where by instance
      refers to object instance of a Class.

    'class instance variable'
      Variables that are defined using @<instance_variable> syntax under 
      class definition and class_methods belonging to the Class and available to
      all instance of the Class ???

    'class variable'
      Available to instance method and class method.

    'Constant variable'
      Available to any external code which can access the Class object.

    'class-method'
      Availble to any external code which can access the Class object.

    'instance-method'
      Available to any external code which can access the instance object.

  TODO : Add scope resolution nomenclature and fundamentals for modules.

  Since the 'Kernel module' is included by Object class, its methods are
  available everywhere in the Ruby program. They can be called without a
  receiver (functional form). Therefore, they are often called functions
  (built-in functions)

  Build-ins : 

  object.id
  symbol.to_i.id2name, symbol.to_s, symbol.to_i.to_sym
  <obj>.class
  <obj>.superclass

  * object.id has nothing to do with symbol id (symbol.to_i)

  Predefined variables : 

  $:
    Array of directory path that will used as search path for 'require',
    'load'
  $!
    Last Exception.
  $/
    Record separator. Used by methods such as `gets` and `chomp`.
  $&
    ???

Glossary : 

  reciever - object that is receives the message.
  message - everything is message passing (abstractly speaking).
  host class - that includes the module as mixin.
