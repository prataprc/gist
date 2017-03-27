#! /usr/bin/env python

import argparse
import sys
import time

parser = argparse.ArgumentParser(description='parser redis log file')
parser.add_argument('--logfile', dest='logfile', action='store',
                    default='', help='provide redis logfile')
parser.add_argument('--from', dest='fromtime', action='store',
                    default='', help='provide redis logfile')
parser.add_argument('--till', dest='tilltime', action='store',
                    default='', help='provide redis logfile')
args = parser.parse_args(sys.argv[1:])

if args.fromtime != '' :
    fromtm = time.strptime(args.fromtime, '%b %d %H:%M:%S')
if args.tilltime != '' :
    tilltm = time.strptime(args.tilltime, '%b %d %H:%M:%S')

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
        at = time.strptime(' '.join(tokens[:3]), '%b %d %H:%M:%S')
        if compare(at) == 0 :
            print line

parselines()
