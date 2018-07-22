require "pp.rb"

@help = 'helper'
@@classhelp = 'classhelper'

def i(obj)
    pp(obj.methods)
end

class O
    @@cvar
    @civar
    attr_accessor( :ciattr_var )
    def initialize
        @oivar = 10
        @@covar = 20
    end
end

def meth()
    puts self
    puts self.class
    puts self.inspect
end

@hello = "goof"
aClos = lambda{
    @hello << " yikes!"
    puts("in #{self} object of class #{self.class}, @hello = #{@hello}")
}

class X 
    def y( b )
        @hello = "I say, I say, I say!!!"
        puts( " [In X.y]" )
        puts("in #{self} object of class #{self.class}, @hello = #{@hello}")
        puts( " [In X.y] when block is called..." )
        b.call
    end
end

x = X.new
x.y( aClos )
