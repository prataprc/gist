class prop_ext(property) :
    def __init__(self, *args):
        property.__init__(self, self.extensions)
        print "Initializing property extension, ", args

    def extensions(self, *args):
        """Return a list of components that declare to implement the extension
        point interface.
        """
        print "Property extension called, "
        print "self : ", self
        print "args : ", args

class prop_ext_ext(prop_ext) :
    def __init__(self, *args):
        property.__init__(self, self.extensions, self.extensions)
        print "Initializing property extension, ", args

    def extensions(self, *args):
        """Return a list of components that declare to implement the extension
        point interface.
        """
        print "Property extension extension called, "
        print "self : ", self
        print "args : ", args

class sample(object) :

    def read( *args ) :
        print "Reading ... ", args

    def write( *args ) :
        print "Writing ... ", args

    def delete( *args ) :
        print "Deleting ... ", args
    doc = "Sample."
    baseprop = property(read, write, delete, doc)
    propext = prop_ext_ext(read, write, delete, doc)

s = sample()
b = s.baseprop
c =  s.propext
s.baseprop = 10
s.propext = 20
