#! /usr/bin/env python3

import sys
import re

if len(sys.argv) < 2 :
    print("specify the log file")
    sys.exit(1)

servers = {}

def handler_datp_1(server) :
    #print("datp_1 `%s`" % server)
    servers.setdefault(server, {})

def handler_datp_2(server, raddr) :
    #print("datp_2 `%s` `%s`" % (server, raddr))
    servers[server].setdefault(raddr, {})

def handler_datp_3(server, raddr, bucket, vbno) :
    #print("datp_3 `%s` `%s` `%s` `%s` " % (server, raddr, bucket, vbno))
    servers[server][raddr].setdefault(bucket, []).append(int(vbno))

def handler_datp_4(server, raddr) :
    #print("datp_4 `%s` `%s` " % (server, raddr))
    server in servers and raddr in servers[server] and servers[server].pop(raddr)

def handler_datp_5(server) :
    #print("datp_5 `%s` " % server)
    server in servers and servers.pop(server)

def handler_datp_6(server, raddr, bucket, vbno) :
    #print("datp_6 `%s` `%s` `%s` `%s` " % (server, raddr, bucket, vbno))
    servers[server][raddr][bucket].remove(int(vbno))

def handler_marker(line) :
    for server, sval in sorted(servers.items()) :
        print("server: %s" % server)
        for raddr, rval in sorted(sval.items()) :
            print("   ", "%s: " % raddr, end="")
            for bucket, vbnos in sorted(rval.items()) :
                vbnos.sort()
                if len(vbnos) == 0 : continue
                s = "%s." % vbnos[0]
                for x, y in zip(vbnos, vbnos[1:]) :
                    s += (y-x > 1 and "%s,%s." % (x,y)) or \
                         ((y-x == 1 and s[-1] != "." and ".") or "")
                s += "%s" % vbnos[-1]
                print("%s: " % bucket, s, end=" ")
            print("")
    print(line)
    len(servers) > 0 and print("")

matchers = [
  [ re.compile(r'.*\[Info\] DATP\[->dataport ":([0-9]+)"\] started ...'),
    handler_datp_1 ],
  [ re.compile(r'.*\[Info\] DATP\[->dataport ":([0-9]+)"\] new connection "([^"]+)".*'),
    handler_datp_2 ],
  [ re.compile(r'.*\[Debug\] DATP\[->dataport ":([0-9]+)"\] added vbucket ([^-]+)-([^-]+)-([0-9]+).*'),
    handler_datp_3 ],
  [ re.compile(r'.*\[Debug\] DATP\[->dataport ":([0-9]+)"\] connection "([^"]+)" closed !'),
    handler_datp_4 ],
  [ re.compile(r'.*\[Debug\] DATP\[->dataport ":([0-9]+)"\] ... stopped'),
    handler_datp_5 ],
  [ re.compile(r'.*\[Debug\] DATP\[->dataport ":([0-9]+)"\] deleted vbucket ([^-]+)-([^-]+)-([0-9]+).*'),
    handler_datp_6 ],
  [ re.compile(r'(.*\[Debug\] KVSender::.*)'),
    handler_marker ],
]

booker = {}
for line in open(sys.argv[1]).readlines() :
    for regx, fn in matchers :
        m = regx.match(line)
        if m : fn(*m.groups())
