#!/bin/env python
import os
for i in range(20):
        os.system("dd if=/work/software/pchakravarthy/zcs-4.5.6_GA_1044.SuSE10.tgz count=1000 of=file%d" % i)
        os.system("rm -f ofile%d.bz2" % i)
        os.system("xxd file%d ofile%d" % (i, i))
        os.system("bzip2 ofile%d" % i)
        os.system("bunzip2 ofile%d.bz2" % i)
