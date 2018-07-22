#! /usr/bin/env python

import sys 
import getopt 
import os

usage   = '''
    gpg_zip.py <file_name>
'''

if len(sys.argv) != 2 :
    print usage
    sys.exit(1)

rawfile     = sys.argv[1]
encfile     = rawfile + ".gpg"
zipfile     = encfile + ".zip"
unzipfile   = encfile + ".unzip"
decfile     = rawfile + ".dec"

os.system("gpg -e -r pratap " + rawfile)
os.system("zip " + zipfile + " " + encfile)
os.system("unzip -p " + zipfile + " > " + unzipfile)
os.system("gpg -d -r pratap " + "--passphrase-fd 0 " + unzipfile+" < passwd " \
        + " > " + decfile)
if os.system("diff " + unzipfile + " " + encfile) == 0 :
    print "Matching ", unzipfile, encfile
if os.system("diff " + rawfile + " " + decfile) == 0 :
    print "Matching ", rawfile, decfile

os.system("rm " + encfile + " " + zipfile + " " + unzipfile + " " + decfile)
