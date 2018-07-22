#! /usr/bin/env python

import sys 
import getopt 
import os
import Queue
import threading
import time

sync_sem    = threading.Semaphore(0)

def worker(q=None, fn=None, qlist=None) :
    try:
        fn(q, qlist)
        print "Worker completed for : " + fn.__name__
        sync_sem.release()
    except KeyboardInterrupt :
        print "### KeyboardInterrupt"
        sys.exit(1)
    except:
        print "Help : ", sys.exc_info()
    return

class PPipeline :
    def __init__ (self, fn_list):
        self.qlist  = {}
        self.wlist  = {}
        self.qcount = 0
        for fn in fn_list :
            self.qcount             += 1
            q                       = Queue.Queue()
            self.qlist[fn.__name__] = q
            t = threading.Thread(target=worker, args=(q, fn, self.qlist))
            self.wlist[fn.__name__] = (t, fn, q, self.qlist)
            print self.qcount,"Preparing worker thread for function : ",    \
                                fn.__name__

    def start(self) :
        for key in self.wlist :
            t   = self.wlist[key][0]
            fn  = self.wlist[key][1]
            t.setDaemon(True)
            t.start()
            print "Starting the worker thread for function :", key

        for key in self.wlist :
            sync_sem.acquire()
        for key in self.wlist :
            t   = self.wlist[key][0]
            while t.isAlive() : pass

        return
