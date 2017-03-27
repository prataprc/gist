#! /usr/bin/env python

import argparse
import sys
import time
import re

parser = argparse.ArgumentParser(description='parser redis log file')
parser.add_argument('--logfile', dest='logfile', action='store',
                    default='', help='provide redis logfile')
parser.add_argument('--from', dest='fromtime', action='store',
                    default='', help='provide redis logfile')
parser.add_argument('--till', dest='tilltime', action='store',
                    default='', help='provide redis logfile')
args = parser.parse_args(sys.argv[1:])

def cureline(line) :
    patt = r'([^ ]+)[ ]+([0-9]+)[ ]+([0-9]+:[0-9]+:[0-9]+).*'
    m = re.match(patt, line)
    return ' '.join(m.groups())

def parseline(line) :
    timestr = cureline(line)
    return time.strptime(timestr, '%b %d %H:%M:%S')

if args.fromtime != '' :
    fromtm = parseline(args.fromtime)
if args.tilltime != '' :
    tilltm = parseline(args.tilltime)

def compare(at) :
    if args.fromtime != '' and at < fromtm :
        return -1
    if args.tilltime != '' and at > tilltm :
        return 1
    return 0

def parselines() :
    for line in open(args.logfile).readlines() :
        tokens = line.split(' ')
        if len(tokens) < 3 :
            continue
        at = parseline(line)
        if compare(at) == 0 :
            print line

parselines()
