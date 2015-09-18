#! /usr/bin/env python3

import sys
import re
import json
import argparse

import plotly.plotly as py
from plotly.graph_objs import *

parser = argparse.ArgumentParser(description='periodic stats')
parser.add_argument('--params', dest='params', default="all",
    help='parameters to plot')
parser.add_argument('logfile', nargs=1, help='logfile to parse')
args = parser.parse_args()
args.params = args.params.split(",")

stats = []

def handler_periodicstats(line, dstr) :
    val = json.loads(dstr)
    nval = {}
    for param, value in val.items() :
        try :
            nval[param] = int(value)
        except ValueError :
            nval[param] = 0
            x = value.split(" ")
            if x[0] != '0' :
                nval[param] = int(x[1].strip()) / int(x[0].strip())
    stats.append(nval)

matchers = [
  [ re.compile(r'.*\[Info\].*PeriodicStats = (.*)'),
    handler_periodicstats ],
]

for line in open(sys.argv[1]).readlines() :
    for regx, fn in matchers :
        m = regx.match(line)
        if m : fn(m.group(), *m.groups())

def indexerGraph() :
    params = {}
    if len(args.params) == 1 and args.params[0] == "all" :
        for i, m in enumerate(stats) :
            for param, value in m.items() :
                params.setdefault(param, []).append(int(value))
    else :
        for i, m in enumerate(stats) :
            for param_patt in args.params :
                for param, value in m.items() :
                    if re.compile(param_patt).match(param) :
                        params.setdefault(param, []).append(int(m[param]))

    x = list(range(1, len(stats)+1))
    mode, line = "lines+markers", Line(shape='spline')
    scatters = []
    for param, value in params.items() :
        name = "indexer-%s" % param
        s = Scatter(x=x, y=value, mode=mode, name=name, line=line)
        scatters.append(s)
    data = Data(scatters)
    print(py.plot(data, filename='indexer-graph'))

indexerGraph()
