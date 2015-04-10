#! /usr/bin/env python3

import sys
import re

if len(sys.argv) < 2 :
    print("specify the log file")
    sys.exit(1)

feeds = {}

def handler_proj_call(time, opaque, callname, feedname) :
    #print("proj_call", feedname, callname, opaque)
    feeds.setdefault(opaque, []).extend([feedname, time, callname])

def handler_proj_return(time, opaque, callname) :
    #print("proj_return", callname, opaque)
    feeds.setdefault(opaque, []).append([time, "returned"])

matchers = [
  [ re.compile(r'(^[^ ]+) .*\[Info\] PROJ.*(##[0-9]+) (do[^ ]+).*"([^"]+)".*'),
    handler_proj_call ],
  [ re.compile(r'(^[^ ]+) .*\[Info\] PROJ.*(##[0-9]+) (do[^ ]+).*returns.*'),
    handler_proj_return ],
]

for line in open(sys.argv[1]).readlines() :
    for regx, fn in matchers :
        m = regx.match(line)
        if m : fn(*m.groups())

keys = sorted(feeds.keys(), key=lambda v: int(v[2:]))
for opaque in keys :
    print(opaque, feeds[opaque])
