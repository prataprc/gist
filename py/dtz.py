#! /usr/bin/env python

import datetime as dt
import pytz

d = dt.datetime( 2008, 11, 4, 6, 50, 30, 0, pytz.timezone('UTC'))
for t in pytz.all_timezones :
    tz = pytz.timezone( t )
    print "UTC %s as %s in %s" % (d, tz.normalize(d.astimezone(tz)), tz)
