#! /usr/bin/env python

import pprint
import sys
import xml.etree.cElementTree as xmlet

'''
e is an element instance
'''

e   = xmlet.Comment( 'Hello World' )
ea  = xmlet.Element( 'sampletag', { 'a':'hello' }, b='world' )
es  = xmlet.fromstring( '<this ought="to" be="parsed" by="this">call</this>' )
ex  = xmlet.XML( '<this ought="to" be="parsed" by="this">call</this>' )
ei,ed  = xmlet.XMLID( '<this ought="to" be="parsed" by="this">call</this>' )
if xmlet.iselement( es ) : 
    print "fromstring() successfully created the element"
xmlet.dump( e )
xmlet.dump( ea )
xmlet.dump( es )
xmlet.dump( ex )
xmlet.dump( ei )

ET  = xmlet.parse( 'wav.xml' )
et  = ET.getroot()

if e :
    xmlet.dump( e )
