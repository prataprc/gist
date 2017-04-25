#! /usr/bin/env python

'''
    dir --> dir --> ... --> file ----------------> sym 
     |                        |                     |
     |-> filelist   []        |-> definedsyms   []  |->name
     |-> afilelist  []        |-> undefinedsyms []  |->files
     |-> dirlist    []        |-> symlist {}        |->defines
     |-> adirlist   []        |-> symtypes {}       |->type
     |-> definedsyms   []     |-> globalsyms {}     |->defined
     |-> undefinedsyms []     |-> localsyms {}
     |-> symlist {}
     |-> symtypes{}
     |-> globalsyms {}
     |-> localsyms {}
     |-> dirpath
     |-> parent
'''

import re
import os
import sys
import random
import getopt
import pprint

_symboltypes    = [ 
                    [ 'A', 'B', 'C', 'D', 'G', 'I', 'N', 'R',  'S', 'T', 'U', 'V', 'W' ], 
                    [ 'a', 'b', 'c', 'd', 'g', 'i', 'n', 'r',  's', 't', 'u', 'v', 'w' ], 
                    [ '?' ]
                  ]


NMCMD           = 'nm -C '

def parsenm( objfile ) :
    '''
    Use the 'nm' utitlity to dump the object file for it symbol definitions
    '''
    pass


class NMDir :
    '''
    Dir object containing a list of attributes (explained in the top)
    '''
    def __init__( self, dirpath ):
        self.dirpath        = dirpath
        self.parent         = None
        self.filelist       = []
        self.sfilelist      = []
        self.dirlist        = []
        self.sdirlist       = []
        self.symbols        = {}                # Dictionary of symbol objects { symname : symobject }
        self.globalsyms     = {}                # Dictionary of global symbol types { symtype : [symobject] }
        self.localsyms      = {}                # Dictionary of local symbol types { symtype : [symobject] }


class NMFile :
    '''
    Dir object containing a list of attributes (explained in the top)
    '''
    def __init__( self, filepath ):
        self.filepath       = filepath
        self.symbols        = {}                # Dictionary of symbol objects { symname : symobject }
        self.globalsyms     = {}                # Dictionary of global symbol types { symtype : [symobject] }
        self.localsyms      = {}                # Dictionary of local symbol types { symtype : [symobject] }


class NMSymbol :
    '''
    Dir object containing a list of attributes (explained in the top)
    '''
    def __init__( self, symname, filepath, type ):
        self.name           = symname            # Name of the symbol
        self.files          = [ filepath ]       # List of files it is referenced
        self.type           = type               # Dictionary of symbol objects { symname : [symobject] }


class NMTree :
    '''
    Helper class for source magic
    '''
    def _addnodes( self, dirobj, path, remnodes ) :
        '''
        'dirobj' is parent NMDir directory object
        '''
        node        = remnodes[0]
        nodepath    = os.path.join( path, node )
        if len( remnodes ) == 1 :               # We have reached the file
            dirobj.__dict__[node]   = NMFile( nodepath )
            dirobj.filelist.append( nodepath )
            return ( nodepath, [] )
        elif node not in dirobj.__dict__ :      # Add the directory
            nodeobj     = NMDir( nodepath )
            dirobj.__dict__[node]   = nodeobj
            nodeobj.parent = dirobj             # Backlink to parent directory
            dirobj.dirlist.append( nodepath )
            sfile, sdirs = self._addnodes( nodeobj, nodepath, remnodes[1:] )
        else :                                  # directory node already present
            nodeobj     = dirobj.__dict__[ node ]
            sfile, sdirs = self._addnodes( nodeobj, nodepath, remnodes[1:] )

        if sfile not in dirobj.sfilelist :
            dirobj.sfilelist.append( sfile )
        if sdirs :
            [ dirobj.sdirlist.append( dir ) for dir in sdirs if dir not in dirobj.sdirlist ]
        sdirs.append( nodepath )
        return sfile, sdirs 

    def __init__( self, flist, base='dot' ) :
        '''
        Follow through the directory tree and index.
        'flist' is something like cscope.files
        'base' can be 'root' or 'dot, based on obsolute or relative path names in the 'flist'
        '''
        self.root               = NMDir( base )
        self.__dict__[base]   = self.root

        if not os.path.isfile( flist ) :
            print "Error: %s not a file, please specify a valid file list" % flist
            return False

        for file in open( flist, 'r' ).readlines() :
            file    = file.strip()
            if not os.path.isfile( file ) :
                print "Error: %s not a source file" % file
                continue
            treenodes   = file.split( os.sep )
            treenodes[0]= treenodes[0] or os.sep
            sfile, sdirs= self._addnodes( self.root, treenodes[0], treenodes[1:] ) 
            if sfile not in self.root.sfilelist :
                self.root.sfilelist.append( sfile )
            if sdirs :
                [ self.root.sdirlist.append( dir ) for dir in sdirs if dir not in self.root.sdirlist ]
