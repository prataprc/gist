#! /usr/bin/env python
from commands import getstatusoutput

import sys 
import getopt 
import os
import ppipe
import time

def worker_dd (q, qlist):
    for i in range(20):
        getstatusoutput("dd if=/work/software/pchakravarthy/zcs-4.5.6_GA_1044.SuSE10.tgz count=1000 of=file%d" % i)
        getstatusoutput("rm -f ofile%d.bz2" % i)
        getstatusoutput("xxd file%d ofile%d" % (i, i))
        qlist["worker_zip"].put('ofile%d' % i)
    print "Finish ! 1"
    qlist["worker_zip"].put("done")
    return 

def worker_zip(q, qlist):
    while 1 :
        item = q.get()
        if isinstance(item, str) and item == "done" :
            break;
        print "Zip : ", item 
        getstatusoutput("bzip2 " + item)
        qlist["worker_bunzip"].put(item + ".bz2")
    print "Finish ! 3"
    qlist["worker_bunzip"].put("done")
    return

def worker_bunzip(q, qlist):
    while 1 :
        item = q.get()
        if isinstance(item, str) and item == "done" :
            break;
        print "UnZip : ", item 
        getstatusoutput("bunzip2 " + item)
    print "Finish ! unzip"
    return

def worker_source(q, qlist):
    str         = ["hello","world", "how", "are", "you"]
    for item in str :
        time.sleep(.2)
        qlist["worker_zip"].put(item)
    print "Finish ! 1"
    qlist["worker_enc"].put("done")
    return 

def worker_enc(q, qlist):
    while 1 :
        item = q.get()
        if isinstance(item, str) and item == "done" :
            break;
        print "Enc : ", item 
        time.sleep(.2)
        qlist["worker_zip"].put(item)
    print "Finish ! 2"
    qlist["worker_zip"].put("done")
    return


def worker_dec(q, qlist):
    while 1 :
        item = q.get()
        if isinstance(item, str) and item == "done" :
            break;
        print "Dec : ", item 
        time.sleep(.2)
        qlist["worker_unzip"].put(item)
    print "Finish ! 4"
    qlist["worker_unzip"].put("done")
    return

#def worker_unzip(q, qlist):
    #while 1 :
        #item = q.get()
        #if isinstance(item, str) and item == "done" :
            #break;
        #print "Unzip : ", item 
        #time.sleep(.2)
        #qlist["worker_dest"].put(item)
    #print "Finish ! 5"
    #qlist["worker_dest"].put("done")
    #return

def worker_dest(q, qlist):
    while 1 :
        item = q.get()
        if isinstance(item, str) and item == "done" :
            break;
        print "dest : ", item 
        time.sleep(.2)
    print "Finish ! 6"
    return

try:
    #p = ppipe.PPipeline([worker_source, worker_enc, worker_zip, worker_dec,     \
                         #worker_unzip, worker_dest])
    p = ppipe.PPipeline([worker_dd, worker_zip, worker_bunzip])
    p.start()
    print "Started and ended "
except KeyboardInterrupt :
    print "### KeyboardInterrupt"
    sys.exit(1)
except:
    print "Help : ", sys.exc_info()
