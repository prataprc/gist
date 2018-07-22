module M
    @@cvar = "cvar"
    attr_accessor :bubbly
end

class C
    include M
    class_lvar = "class_lvar"

    def initialize
        @a = 10
    end
    def one
        puts 1
        1.times { |x| puts self.class }
    end
    def two
        one
        self.one
        puts 2
        puts @@cvar
        puts class_lvar
    end
end

def func b, a=[]
    a << b
    return a
end

puts func(10).length
puts func(20).length
