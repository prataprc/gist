#! /usr/bin/env python

from   httplib2     import Http
import lxml.html    as lh

# URLs
START_URL = 'http://eciresults.nic.in/Constituencywises031.htm'
CONST_URL = 'http://eciresults.nic.in/ConstituencywiseS22%s.htm'

# HTTP client
ht = Http()

# Parse Constituency names and urls
hdrs, html = ht.request( START_URL )
root = lh.fromstring( html )
e = root.xpath( '//input[@id="HdnFldTamilNadu"]' )[0]
constit = [ s.strip(';').split(',') 
            for s in e.attrib['value'].split('\r\n') if s ]

# Collect Consituency-wise result details.
details = {}
for x, constname in constit :
    print "Parsing for %s ... " % constname
    hdrs, html = ht.request( CONST_URL % x )
    xroot = lh.fromstring( html )
    rows = xroot.xpath( '//div[@id="div1"]//table[1]/tr' )
    details.setdefault(
        constname, [ rows.xpath( './td/text()' ) for rows in rows[3:] ]
    )

# Write the results in CSV format for each constituency under <constname>.csv
[ open( ('%s.csv'%constname), 'w' ).write(
        '\r\n'.join([ ', '.join(x) for x in details ])
  ) for constname, details in details.items() ]
