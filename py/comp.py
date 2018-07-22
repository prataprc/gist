#! /usr/bin/env python

import pprint
from zope.interface import Interface
from zope.interface import implements
from zope.component import getGlobalSiteManager
from zope.component import queryUtility
from zope.component import getUtility

class IGreeter(Interface):
    def greet(name):
        """Say hello"""

class Greeter1(object):
    implements(IGreeter)
    def greet(self, name):
        return "Hello " + name

class Greeter2(object):
    implements(IGreeter)
    def greet(self, name):
        return "Hello " + name

gsm = getGlobalSiteManager()

g1, g2 = Greeter1(), Greeter2()

gsm.registerUtility( g1, IGreeter, )
gsm.registerUtility( g2, IGreeter, )

a = [ x for x in gsm.registeredUtilities() ][0]
print a.component == g2, a.factory, len(a.info), a.name, a.provided == IGreeter, a.registry

print queryUtility(IGreeter )
print getUtility(IGreeter, 'first')
