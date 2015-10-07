#! /usr/bin/env python3

import sys
import re
import argparse
import fileinput
import time
import datetime as dt

parser = argparse.ArgumentParser(description='parse and plot stats')
parser.add_argument('--kind', nargs=1, type=str, default="",
       help='kind of analysis')
parser.add_argument('logfile', nargs=1, help='logfile to parse')
args = parser.parse_args()

def kind_preq(session) :
    calls = {} # opaque -> callname -> (topic, start, end)
    def handler_proj_call(tm, opaque, callname, topic) :
        calls.setdefault(opaque, {}).setdefault(callname, []).extend([topic, tm])
    def handler_proj_return(tm, opaque, callname) :
        calls[opaque][callname].append(tm)

    matchers = [
      [ re.compile(r'(^[^ ]+) .*\[Info\] PROJ.*(##[0-9a-z]+) (do[^ ]+).*"([^"]+)".*'),
        handler_proj_call ],
      [ re.compile(r'(^[^ ]+) .*\[Info\] PROJ.*(##[0-9a-z]+) (do[^ ]+).*returns.*'),
        handler_proj_return ],
    ]
    print(session[0].strip())
    print("number of lines:", len(session))
    for line in session:
        for regx, fn in matchers :
            m = regx.match(line)
            if m : fn(*m.groups())

    topics = {} # topic -> callname -> (n, avg, min, max, opaques)
    for opq, v1 in calls.items() :
        for cn, v2 in v1.items() :
            if len(v2) == 3 :
                start = time.strptime(v2[1][:19], "%Y-%m-%dT%H:%M:%S")
                end = time.strptime(v2[2][:19], "%Y-%m-%dT%H:%M:%S")
                start = dt.datetime.fromtimestamp(time.mktime(start))
                end = dt.datetime.fromtimestamp(time.mktime(end))
                topic, d = v2[0], (end - start).total_seconds()
                m = topics.setdefault(topic, {}
                        ).setdefault(cn, (0, 0, 1000000000, 0, []))
                n = m[0]
                avg = ((m[1]*n) + d) / (n+1)
                mn = (d < m[2] and d) or m[2]
                mx = (d > m[3] and d) or m[3]
                opaques = m[4]
                opaques.append(opq)
                topics[topic][cn] = (n+1, avg, mn, mx, opaques)
            else :
                print("topic started but never ended", opq, v2)
                pass
    for topic, cnmap in topics.items() :
        print("  %s" % topic)
        for cn, (n, avg, mn, mx, opaques) in cnmap.items() :
            mn = 0 if (mn == 1000000000) else mn
            print(
                    "    %s: count:%d avg:%d min:%d max:%d opqs:%s" % (
                    cn, n, avg, mn, mx, opaques))
    print()

def sessions(logfile):
    marker = "Projector started with command line"
    sess, alls = [], []
    for line in fileinput.input(logfile):
        if (marker in line) and len(sess) > 0 :
            alls.append(sess);
            sess = [line]
            continue
        sess.append(line)
    if len(sess) > 0 : alls.append(sess)
    print("total sessions", len(alls))
    return alls


if args.kind[0] == "preq" :
    [ kind_preq(sess) for sess in sessions(args.logfile[0]) ]
