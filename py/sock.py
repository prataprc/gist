#! /usr/local/bin/python

import os, socket, string, sys


s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(("localhost", 9998))
r, addr = s.recvfrom(512)
print r
s.sendto("Hi", ("localhost",9998) )
r, addr = s.recvfrom(512)
print r
