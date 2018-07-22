import sys

print sys.path
sys.path.insert(0, '/home/pratap/dev/trac/trac-trunk/trac/')

import core
from core import *

class ITodoObserver(Interface):
    def todo_added(name, description):
        """Called when a to-do item is added."""

class TodoList(Component):
    observers = ExtensionPoint(ITodoObserver)
    def __init__(self):
        self.todos = {}

    def add(self, name, description):
        assert not name in self.todos, 'To-do already in list'
        self.todos[name] = description
        print "Invoking the plugins ..."
        for observer in self.observers:
            observer.todo_added(name, description)

class TodoPrinter(Component):
    implements(ITodoObserver)

    def todo_added(self, name, description):
        print 'TODO:', name 
        print '     ', description

comp_mgr = core.ComponentManager()
todo_list = TodoList(comp_mgr)

todo_list.add('Make coffee', 'Really need to make some coffee')
todo_list.add('Bug triage', 'Double-check that all known issues were addressed')
