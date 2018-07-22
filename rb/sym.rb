module One
    class Fred
    end
    $f1 = :Fred
    def self.evalFred( aSymbol )
        puts( eval( aSymbol.id2name ) )
    end
end

module Two
    Fred = 1
    $f2 = :Fred
    def self.evalFred( aSymbol )
        puts( eval( aSymbol.id2name ) )
    end
end

def Fred()
    puts( "hello from the Fred method" )
end
$f3 = :Fred
One::evalFred( $f1 ) #=> displays the module::class name: One::Fred
Two::evalFred( $f2 ) #=> displays the Fred constant value: 1
method($f3).call #=> calls Fred method: displays: # “hello from the Fred method”
