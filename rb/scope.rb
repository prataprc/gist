main_local = "main local"
$main_global = "main global"
Mainconst = "main constant"
@main_ivar  = "main ivar"
@@main_cvar = "main cvar"

module M
    mod_local = "mod local"
    $mod_global = "mod global"
    Modconst = "mod const"
    @ivar_mod = "mod ivar"
    @@cvar_mod = "mod cvar"

    def imeth_mod
        puts "module imeth_mod, #{self}"
        puts "#{$main_global}, #{$mod_global}, #{Mainconst}, #{Modconst}"
        puts "#{}, #{}"
        puts ""
        return @ivar_mod, @@cvar_mod, M::Modconst
    end

    def M.mmeth_mod
        puts "module mmeth_mod, #{self}"
        return @ivar_mod, @@cvar_mod, M::Modconst
    end
end

class Base
    include M

    cls_local = "base class local"
    $cls_global = "base class global"
    BaseClsconst = "base class const"
    @ivar_cls = "base class ivar"
    @@cvar_cls = "base class cvar"

    def imeth_base
        super
        puts "base class imeth_base, #{self}"
    end

    def Base.cmeth_mod
        puts "base class cmeth_base, #{self}"
    end
end

class C
    cls_local = "class local"
    $cls_global = "class global"
    Clsconst = "class const"
    @ivar_cls = "class ivar"
    @@cvar_cls = "class cvar"

    def imeth_class
        puts "class imeth_class, #{self}"
    end

    def C.cmeth_class
        puts "class cmeth_class, #{self}"
    end
end

puts self
puts self.class
puts @main_ivar
puts @@main_cvar
puts Mainconst
