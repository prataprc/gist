#! /usr/bin/env python

import sys
import parser
import getopt 

fd      = open(sys.argv[1], "r")
source  = fd.read()
print source
ast = parser.expr("a+2")
print ast.totuple()
