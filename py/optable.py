#! /usr/bin/env python

import os
import re
import sys
from types import NoneType
from pprint import pprint

sys.path.insert( 0, '/home/pchakravarthy/bin' )

import elementtree.ElementTree as et

#--------------- Generic code to any xml ----------------------------

CH          = '\n '
root        = None
xmlfile     = ''

_intokeyslist = lambda dobj, key, value : ( key in dobj and dobj[key].append( value )) or dobj.setdefault( key, [value] )

# Dictionary of unique tags, with a list of element for each key { tag: [element-list] ... }
tags        = {}
gettags     = lambda root, tags  : [ _intokeyslist( tags, e.tag, e ) for e in root.getiterator() ]

# Dictionary of unique tags, with a list of non-repeating text contents
texts       = {}
gettexts    = lambda root, texts : [ _intokeyslist( texts, e.tag, e.text.strip( CH ) for e in root.getiterator() ] and \
                                   dict( [ (tag, list( set( texts[tag] ))) for tag in texts.keys() ] )

# Somtimes the element's text will have fields formated inside, these functions help to reduce repeating fields of the text. 
# The parameter 'dictn' is same as the data type returned by gettexts() function
reducetext  = lambda text, sep   : ( isinstance( text, str ) and list( set( text.split( sep )))) or []
reducelist  = lambda txlist, sep : list( set( [ f for text in txlist for f in reducetext( text, sep ) ] ))
reducealist = lambda dictn, sep  : dict( [ (tag, reducelist( dictn[ tag ], sep )) for tag in dictn.keys() ] )

# Format the xml file into a tree of tags. Used to get an understanding of the tag hierarchy
ct          = {}
_children   = lambda tag, root   : list( set( [ c.tag for e in root.getiterator() if e.tag == tag for c in e.getchildren() ] ))
_ctree      = lambda tlist, root : dict( [ (tag, _ctree( _children( tag, root), root)) for tag in tlist ] )
ctree       = lambda root        : _ctree( [ root.tag ], root )

# Create a database of the xml texts and tags for future greps
_frame_text = lambda par    : par.tag + ':' + par.text.strip( CH ) + '__'
_xmldb      = lambda par    : ((par.text and _frame_text( par )) or (isinstance( par.text, NoneType) and '')) + \
                                    ''.join( [ _xmldb( c ) for c in par.getchildren() ] )

_filter     = lambda text, patts    : [ tagged for tagged in text.split( '__' ) for patt in patts.split( ',' ) if patt in tagged ]
_grep       = lambda db, ip, op, mp: [ '__'.join(_filter(text, mp) + _filter(text, op)) for text in db for patt in ip.split( ',' ) \
                                    if patt in text if _filter( text, op) ]

#----------------------- Specific to instr-optable xml -----------------

xmldb       = {}
def init( file ) :
    '''
    '''
    global tags, texts, ct, xmlfile, root, xmldb
    xmlfile = file
    root    = et.parse( xmlfile ).getroot()
    texts   = gettexts( root, texts )
    ct      = ctree( root )
    tags    = {}
    gettags( root, tags )
    if 'optable' in xmlfile :       # Instruction optable
        xmldb[ root.tag ]   = [ _xmldb( c ) for c in root.getchildren() ]
    if 'knob' in xmlfile :          # Monster knobs
        if root.tag == 'all' :
            [ xmldb.setdefault( dbchild.tag,  [ dbchild.tag + '__' + _xmldb( c) for c in dbchild.getchildren() ] ) \
                        for dbchild in root.getchildren() ]
    return 

def grep( ipatts, opatts ) :
    '''
        For now,
        ipatts  - comma seperated patterns to match the text
        opatts  - comma seperated patterns to filter the matching text with matching patterns

        Later, nice to have
        ipatts Notation,
            [qualifier]pattern,[qualifier]pattern ...

            Qualifiers are,
            :t: the following pattern is for tag lookup
            :x: the following pattern is for text lookup
            :+: add the results matched by following pattern to preceding results
            :-: remove the results matched by following pattern from preceding results
        opatts Notation,
            [qualifier]pattern,[qualifier]pattern ...

            Qualifiers are,
            :t: Display only the tag fields matching the pattern
            :x: Display only the tag fields matching the pattern

            The above qualifiers/patterns are to select the tag-text field, display will be for both tag and text
    '''
    mandpatts   = ''
    if 'optable' in xmlfile and 'Full' not in opatts :
        mandpatts   = 'Full'
    mlist   = []
    [ mlist.extend(  _grep( xmldb[key], ipatts, opatts, mandpatts )) for key in xmldb.keys() ]
    for fulltext in mlist :
        otext   = ''
        for tagtext in fulltext.split( '__' ) :
            if len( otext ) > 120 :
                otext.replace( '__', ', ' )
                print otext
                otext = ''
            else :
                otext += ', ' + tagtext
        if otext :
            otext.replace( '__', ', ' )
            print otext
