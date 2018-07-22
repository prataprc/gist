#! /usr/bin/env python

import sys
import re

x = r'((\d+\.\d*)|(\d*\.\d+)|(?P<int>\d*))(?(int)e(\+|-)?\d+|(e(\+|-)?\d+)?)'

m = re.match(x,"1") 
if m : print m.group()
m = re.match(x,".") 
if m : print m.group()
m = re.match(x,"1.") 
if m : print m.group()
m = re.match(x,".1") 
if m : print m.group()
m = re.match(x,"1.1") 
if m : print m.group()
print

m = re.match(x,"1e+") 
if m : print m.group()
m = re.match(x,".e-") 
if m : print m.group()
m = re.match(x,"1.e+") 
if m : print m.group()
m = re.match(x,".1e-") 
if m : print m.group()
m = re.match(x,"1.1e+-") 
if m : print m.group()
print

m = re.match(x,"1e1") 
if m : print m.group()
m = re.match(x,".e1") 
if m : print m.group()
m = re.match(x,"1.e1") 
if m : print m.group()
m = re.match(x,".1e1") 
if m : print m.group()
m = re.match(x,"1.1e1") 
if m : print m.group()
print

m = re.match(x,"1e+1") 
if m : print m.group()
m = re.match(x,".e+1") 
if m : print m.group()
m = re.match(x,"1.e+1") 
if m : print m.group()
m = re.match(x,".1e+1") 
if m : print m.group()
m = re.match(x,"1.1e+1") 
if m : print m.group()
print

m = re.match(x,"1e-1") 
if m : print m.group()
m = re.match(x,".e-1") 
if m : print m.group()
m = re.match(x,"1.e-1") 
if m : print m.group()
m = re.match(x,".1e-1") 
if m : print m.group()
m = re.match(x,"1.1e-1") 
if m : print m.group()
print
