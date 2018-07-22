applymod = lambda m, f, args : m.__dict__[f]( *args )
apply    = lambda f, args    : globals()[f]( *args )
