#! /usr/bin/env python

'''
This program attempts to consolidate the linux development environment for both
administrative purpose and user purpose. Since I am a debian user, I have
built this script as I kept working on my debian box.
'''

import optparse
import commands
import logging
import sys
import os
import re

_bin_dirs = [ '/bin', '/sbin', '/usr/bin', '/usr/local/bin', 
              '/usr/local/sbin' ]

_services =['portmap', 'rpc.mountd', 'rpc.nfsd',
            'smbd', 'nmbd',
            'automount',
            'named',
            'lpd',
            'inetd',
            'telnet', 'rlogin', 'rexec', 'ftp',
            'finger', 'comsat', 'chargen', 'echo', 'identd',
            'dictd', 'apache']
    

_sectcount = 1

def _logcmderror( log, status, output ) :
    '''
    Use the parameters and log the Output of the command.
    '''
    logging.error( log + " Status :", status )
    for o in output :
        print "    %s", o

def _logsection( secname ) :
    '''
    Each administration detail is cataloged under unique section head.
    '''
    global _sectcount
    print "\n%d. %s :\n" % (_sectcount, secname)
    _sectcount += 1


def env_init( options ) :
    '''
    All the environment details for the init process.
    '''

    _logsection( "System and Kernel environment" )

    # persistent daemon using 'init'. 
    # TODO: Check whether Ubuntu and if so use upstart to check for the
    # corresponding configurations.
    if os.path.isfile( '/etc/inittab' ) :
        logging.error( "/etc/inittab file found : Better the script to parse the inittab" )
    else :
        print "/etc/inittab : File not found"

    # Linux version
    print "Running linux version : %s" % open( '/proc/version').read().strip()

    # Memory detected
    cmd = 'ls -l /proc/kcore'
    status, output = commands.getstatusoutput( cmd )
    print "Detected memory : %s" % output.strip()

    # Interrupts
    cmd = 'cat /proc/interrupts'
    status, output = commands.getstatusoutput( cmd )
    print "Interrupts : \n %s" % output.strip()

    # Partitions
    cmd = 'cat /proc/partitions'
    status, output = commands.getstatusoutput( cmd )
    print "Partitions : \n %s" % output.strip()




def special_bins() :
    '''
    Collect all the files that have setuid / setgid bits set.
    '''
    _logsection( "Files with setuid and setgid" )

    specialbins = []
    for d in _bin_dirs :
        cmd = 'find ' + d + ' -perm +6000 -type f -exec ls -ld {} \;'
        status, output = commands.getstatusoutput( cmd )
        if output :
            specialbins.extend( output.split('\n') )
    if specialbins :
        for f in specialbins :
            print f


def Daemons( options ) :
    '''
    Check for the running Daemons and its configurations
    '''
    
    _logsection( "Daemons" )

    # Daemons detected through 'ps'
    pscmd = 'ps -eo user,pid,tty,time,%cpu,%mem,cmd'
    status, output = commands.getstatusoutput( pscmd )
    output = output.split('\n')
    status and _logcmderror( "Failed : %s" % pscmd, status, output )
    stp_services = _services[:]
    str_services = [ (service, psentry) for service in _services \
                     for psentry in output if re.search( service, psentry ) ]
    [ stp_services.remove(service) for service, psentry in str_services \
                                   if service in stp_services ]
    if options.inverse :
        print "Daemon %s are stopped" % stp_services
    else :
        for service, psentry in str_services :
            print '%-10s .... running (%s)' \
                   % (service, ' '.join(re.findall('[^ ]+', psentry)[6:]))

    print ""

    # Daemons in /etc/inetd.conf
    inetd_services = []
    for line in open( '/etc/inetd.conf' ).readlines() :
        if line[0] != '#' :
            inetd_services.append( line.strip() )
    if inetd_services :
        print "Daemons registered and active in /etc/inetd.conf,"
        for s in inetd_services :
            print "%-10s" % s


def debian_version( options ) :
    '''
    Check out the debian version information from the following files,
    /etc/issue
    /etc/debian_version
    /etc/apt/sources.list
    '''

def option_parse() :
    '''
    Parse the options and check whether the semantics are correct.
    '''
    parser  = optparse.OptionParser(usage="usage: %prog [options] commmands")
    parser.add_option( '-v', dest='inverse', action='store_true', \
                        default=False, help='Inverse of the result' )
    options, args   = parser.parse_args()

    return parser, options, args


if __name__ == '__main__' :
    logging.basicConfig( level=logging.INFO )
    parser, options, args = option_parse()
    env_init(options)
    Daemons(options)
    special_bins()
