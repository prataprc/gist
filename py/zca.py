from zope.interface import Interface
from zope.interface import implements

class IGreeter(Interface):
    def greet(name):
        """Say hello"""

class Greeter(object):
    implements(IGreeter)
    def greet(self, name):
        return "Hello " + name


from zope.component import getGlobalSiteManager
gsm = getGlobalSiteManager()
greet = Greeter()
greet1 = Greeter()
gsm.registerUtility(greet, IGreeter)
gsm.registerUtility(greet1, IGreeter)

from zope.component import queryUtility
from zope.component import getUtility
print queryUtility(IGreeter)
print getUtility(IGreeter)
