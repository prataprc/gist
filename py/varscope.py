#! /usr/bin/env python

g_val1 = "global-string1"
g_val2 = "global-string2"

def func( arg1, arg2 ) :
    def n1_func( n1_arg1, n1_arg2 ) :
        f = lambda x : g_val1 and arg1 and arg2 and n1_arg1 and n1_arg2 and (locals(), globals())
        print "##########-----------------###############"
        print locals()
        print "##########-----------------###############"
        print globals()
        print arg1, arg2, n1_arg1, n1_arg2, g_val1, g_val2
        print "##########-----------------###############"
        l, g = f( 1001 )
        print l
        print "##########-----------------###############"
        print g
        arg1 = "modified"
        arg2 = "modified twice"
    print "##########-----------------###############"
    print locals()
    print "##########-----------------###############"
    print globals()
    print g_val1, g_val2

    n1_func( 100, 200 )


func( 10, 20 )
