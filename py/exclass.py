class base :
    a = 0
    def __init__(self, list) :
        print "Initializing the base class"
        for each in list :
            self.__dict__[each] = base.a;
            base.a += 1

class derived(base) :
    def __init__(self, list) :
        print "Initializing the derived class"
        base.__init__(self, list)

class meta_class(type) :
    def __new__( cls, name, bases, d ) :
        print "__new__ called for Meta class "
        print "cls : ", cls
        print "name : ", name
        print "bases : ", bases
        print "d : ", d
        new_class = type.__new__(cls, name, bases, d)
        #print "...", new_class.mro()[0].__init__._original
        return new_class


class newbase(object) :
    a = 0
    __metaclass__ = meta_class
    def __new__( cls, *args, **kargs ) :
        print "__new__ for the newbase class"
        print "cls :", cls
        print "args :", args
        print "kargs :", kargs
        self = super(newbase, cls).__new__(cls)
        print "self created of type : ", type(self)
        return self

    def __init__(self, list) :
        print "Initializing the newbase class"
        for each in list :
            self.__dict__[each] = newbase.a;
            newbase.a += 1

class newderived(newbase) :
    b = 0
    #def __new__( cls, *args, **kargs ) :
    #    print "__new__ for the newderived class"
    #    print "cls :", cls
    #    print "args :", args
    #    print "kargs :", kargs

    def __init__(self, list) :
        print "Initializing the newderived class"
        newbase.__init__(self, list)
        print dir(super(newderived))
        print dir(super(newbase))

#b = base(['var1', 'var2'])
#d = derived(['var1', 'var2'])
#
#x = newbase(['var1', 'var2'])
#y = newderived(['var1', 'var2'])
#print "Is y instance of newbase : ", isinstance(y, newbase)
#print "Is y instance of newderived : ", isinstance(y, newderived)
