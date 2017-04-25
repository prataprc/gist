#! /usr/bin/env python

import os
import re
import sys
import optparse
import commands
from pprint import pprint

dpkgstatus_file = '/var/lib/dpkg/status'

def getpkggraph( outfile=None ) :
    '''
    Use the apt-cache command to obtain the entire list of package as a
    dependency graph between packages.
    If, outfile is specified, the output will be written to the file, else it
    will printed on the screen.
    Return the output as well.
    '''
    cmd = 'apt-cache dotty'
    status, output = commands.getstatusoutput( cmd )
    if status == 0 :
        if outfile :
            open( outfile , 'wb' ).write( output )
    else :
        print "Error : %s ... returned with %d" % ( cmd, status )
    return output


def getpkgnames( outfile=None ) :
    '''
    Use the apt-cache command to obtain the entire list of package.
    If, outfile is specified, the output will be written to the file, else it
    will printed on the screen.
    Return the output as well.
    '''
    cmd = 'apt-cache pkgnames'
    status, output = commands.getstatusoutput( cmd )
    if status == 0:
        if outfile :
            open( outfile , 'wb' ).write( output )
        else :
            print output
    else :
        print "Error : %s ... returned with %d" % ( cmd, status )
    return output


def getpkgstatus( statusfile ) :
    '''
    Read the dpkg-status file, parse them to create a dictionary of package
    and its status.
    statusfile, is the dpkg-status file that contains the list of package
    details.
    Note : This package list does not include the entire list specified by the
    respository. Just the ones that are available on the host.
    '''
    dpkgstatus = {}
    pkgname = ''
    if os.path.isfile( statusfile ) :
        fd = open( statusfile, 'r' )
        for line in fd.readlines() :
            if line[0:9] == 'Package: ' :
                pkgname = line.split(': ')[1]
                if pkgname in dpkgstatus :
                    print "Error : %s package repeats" % pkgname
                    break
                dpkgstatus[pkgname] = {}
            if line[0] == ' ' :
                dpkgstatus[pkgname][field] += line
                continue
            if line[0] == '\n' :
                continue
            field, content = line.split(':')[0], ''.join(line.split(':')[1:])
            dpkgstatus[pkgname][field] = content
        fd.close()
    return dpkgstatus


def installedpkgs( pkgnames ) :
    '''
    Use dpkg-query -s to find the status of the package
    '''
    pkginstalld = []
    for p in pkgnames :
        status, output = commands.getstatusoutput( 'dpkg-query -s ' + p )
        if status == 0 :
            pkginstalld.append( p )
    return pkginstalld


def filesinpkg( pkgname, verify=False ) :
    '''
    Use dpkg-query -L to obtain the list of files owned by pkgname.
    If verify is True, then check whether the files are present.
    Return the list files.
    '''
    status, output = commands.getstatusoutput( 'dpkg-query -L ' + pkgname )
    flist = []
    divlist = []
    misslist = []
    if status == 0:
        flist = output.split( '\n' )
        [ (flist.remove(f), divlist.append( f.split(' ')[-1] )) \
                for f in flist if f[0:11] == 'diverted by']
        misslist = verify and [ f for f in flist if not os.path.exists( f ) ]
    else :
        print "filesinpkg : Error obtaining the list of files owned by package", pkgname
    return flist, divlist, misslist


def getunaccfiles( dirlist, allpkgfiles ) :
    '''
    Return the list of files Under Standard File System Hierarchy that are not
    owned by any packages
    'dir' specifies the list of directories (absolute path) in standard FSH
    '''
    accfiles = []
    unaccfiles = []
    [ accfiles.extend( allpkgfiles[p] ) for p in allpkgfiles ]
    for dir in dirlist :
        for path, dirs, files in os.walk( dir ) :
            dirs = [ os.path.join( path, d ) for d in dirs ]
            files = [ os.path.join( path, f ) for f in files ]
            unaccfiles.extend([ d for d in dirs if d not in accfiles ] + \
                              [ f for f in files if f not in accfiles ])
    return unaccfiles


def get_fields( dpkgstatus ) :
    '''
    Get a complete list of all the fields in all packages
    '''
    return [ fld for pkg in dpkgstatus for fld in dpkgstatus[pkg].keys() ]


def get_fieldcontents( dpkgstatus, field ) :
    '''
    Get all the contents of a particular 'field', for all the packages.
    '''
    return [ dpkgstatus[pkg][fld].strip() for pkg in dpkgstatus 
                for fld in dpkgstatus[pkg].keys() if fld == field ]


def option_parse() :
    '''
    Parse the options and check whether the semantics are correct.
    '''
    # FIXME : How to add detailed help for command ?
    commands = ['dotty', 'pkgnames', 'pkgstatus', 'depgraph', 'attrs',
                'fieldlist', 'prlist', 'seclist']
    parser  = optparse.OptionParser(usage="usage: %prog [options] command",
                description="command should be one of" + " %s "%commands )
    parser.add_option( '--priority', dest='priority', type='string', \
                       default='', help='Priority of the debian package' )
    parser.add_option( '--section', dest='section', type='string', \
                       default='', help='Debian package section' )
    parser.add_option( '--pkg', dest='pkg', type='string', \
                       default='', help='Debian package name' )

    options, args   = parser.parse_args()
    if len(args) < 1 :
        parser.print_help()
        sys.exit(1)
    if args[0] not in commands :
        parser.print_help()
        sys.exit(1)

    return options, args


if __name__ == '__main__' :
    options, args = option_parse()

    args[0] == 'pkgnames' and getpkgnames()
    if args[0] == 'dotty' :
        output = getpkggraph()
        print output
    if args[0] == 'depgraph' and options.pkg :
        fd = open( '/tmp/tmp.depgraph', 'w' )
        dotout = getpkggraph().split('\n')
        fd.write( '\n'.join(dotout[0:3]) )
        fd.write( '\n'.join([ line for line in dotout \
                                if re.search(options.pkg, line) ]) )
        fd.write( dotout[-1] )
        os.system( 'zgrviewer.sh /tmp/tmp.depgraph &' )
        fd.close()

    dpkgstatus = getpkgstatus( dpkgstatus_file )
    packages = dpkgstatus.keys()
    fields = list(set(get_fields(dpkgstatus)))
    sections = list(set(get_fieldcontents( dpkgstatus, 'Section' )))
    priority = list(set(get_fieldcontents( dpkgstatus, 'Priority' )))
    sections.sort()
    priority.sort()
    fields.sort()

    if args[0] == 'seclist' :
        for s in sections :
            print s,
    if args[0] == 'prlist' :
        for p in priority :
            print p,
    if args[0] == 'fieldlist' :
        for f in fields :
            print f,
    if args[0] == 'pkgstatus' :
        if options.section  :
            packages = [ pkg for pkg in packages \
                    if dpkgstatus[pkg]['Section'].strip() == options.section ]
        if options.priority :
            packages = [ pkg for pkg in packages \
                    if dpkgstatus[pkg]['Priority'].strip() == options.priority ]
        if packages != dpkgstatus.keys() :
            packages = [ pkg.strip() for pkg in packages ]
            packages.sort()
            for p in packages :
                print p,
    if args[0] == 'attrs' :
        attributes = set([ key for pkg in packages for key in dpkgstatus[pkg].keys() ])
        for a in list(attributes) :
            print a,
