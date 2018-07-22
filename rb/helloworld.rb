class Obj
    def *(a)
        puts( "hello, world!" )
        puts(a)
        a*10
    end
end

obj = Obj.new
puts(obj * 2)
