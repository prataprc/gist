import threading

def f( *args ) :
    print args

t = threading.Thread( None, f, 'name', args=(10, 20) )
t.start()
t.run()
