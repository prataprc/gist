#! /usr/bin/env python

# File Hierarchy Standard
#   dir, file, sym, shareable, unshareable, static, variable, config
#   required, optional, incpatt, excpatt

# Attributes of a file may be,
#   "shareable" or "unshareable"    /   "static" or "variable"
#   "root" or "alluser"

# Root FS :
#   The following directories or symbolic links to directories are required in
#   /
#       bin,    boot,   dev,    etc,    lib,    media,  
#       mnt,    opt,    sbin,   srv,    tmp,    usr,    var
#
#   The following directories or symbolic links to directories are required if
#   the corresponding subsystem is installed.
#   /   
#       home,   lib<qual>,  root

# /usr/, /var/, /opt/ are designed such that they can be located on other
# partitions or filesystems.


att_shareable   = [ '/usr/', '/opt/', '/var/mail/', '/var/spool/news' ]
att_unshareable = [ '/etc/', '/boot/', '/var/run/', '/var/lock/' ]

att_static      = [ '/etc/', '/usr/', '/opt/', '/boot/', ]
att_variable    = [ '/var/mail/', '/var/spool/news', '/var/run/', '/var/lock/' ]

dir_root        = (
    '/',
    [ 'boot/', 'dev/', 'etc/', 'lib/', 'home/' ]
    [ 'lib,*/' ]
)

# Rules and Rationale
#   1. bash behaves differently when called as 'sh' or 'bash'.
#   2. '[' and 'test' should be placed together under /bin or /sbin
#   3. If 'gunzip' and 'zcat' programmes exist, they must be symbolic or hard
#      links to gzip. 
#   4. /bin/csh may be a symbolic link to /bin/tcsh or /usr/bin/tcsh
#   5. 'tar', 'gzip' and 'cpio' commands are provided if the need for
#      restoration is there
dir_bin     = ( 
    '/bin/', 
    # Required files
    [ 'cat', 'chgrp', 'chmod', 'cat', 'chgrp', 'chmod', 'chown', 'cp', 'date',
      'dd', 'df', 'dmesg', 'echo', 'false', 'hostname', 'kill', 'ln', 'login',
      'ls', 'mkdir', 'mknod', 'more', 'mount', 'mv', 'ps', 'pwd', 'rm', 'rmdir',
      'sed', 'sh', 'stty', 'su', 'sync', 'true', 'umount', 'uname' ]
    # Optional files
    [ 'csh', 'ed', 'tar', 'cpio', 'gzip', 'gunzip', 'zcat', 'netstat', 'ping',
      'ftp', 'tftp' ]
)

# FIXME: Configuration files and sector map files, boot loader, kernel.
dir_boot    = (
    '/boot/',
    [],
    []
)

# FIXME: List of device files
dir_dev     = (
    '/dev/',
    [],
    [ 'MAKEDEV', 'MAKEDEV.local' ]
)

# Rules and rationale
#   1. 'mtab' is not a static file, but it is kept under '/etc/' for
#      historical reasons.
#   2. No binaries should be located under /etc/
dir_etc     = (
    '/etc/',
    [ 'opt/', 'X11/', 'sgml/', 'xml/' ],
    [ 'csh.login', 'exports', 'fstab', 'ftpusers', 'gateways', 'gettydefs',
      'group', 'host.conf', 'hosts', 'hosts.allow', 'hosts.deny', 'hosts.equiv',
      'hosts.lpd', 'inetd.conf', 'inittab', 'issue', 'ld.so.conf', 'motd', 
      'mtab', 'mtools.conf', 'networks', 'passwd', 'printcap', 'profile', 
      'protocols', 'resolv.conf', 'rpc', 'securetty', 'services', 'shells', 
      'syslog.conf' ]
)

dir_etc_opt     = (
    '/etc/opt/',
    [],
    []
)

dir_etc_X11     = (
    '/etc/opt/',
    [],
    [ 'Xconfig', 'XF86Config', 'Xmodmap' ]
)

dir_etc_sgml    = (
    '/etc/sgml/',
    [],
    [ 'catalog', r'*.conf', r'*.cat' ]
)

dir_etc_xml     = (
    '/etc/xml/',
    [],
    [ 'catalog', '*.conf' ]
)

# Rules and Rationale,
#   The '/lib/' directory contains those shared library images needed to boot
#   the system and run the commands (in '/bin/' and '/sbin/' in the root 
#   filesystems.
dir_lib         = (
    '/lib/',
    [ r'libc.so.*', r'ld.*', r'cpp/', r'modules/' ],
    []
)

dir_home        = (
    '/home/',
    [],
    []
)

dir_media       = (
    '/media/',
    [ 'floppy/', 'cdrom/', 'cdrecorder/', 'zip/' ],
    []
)

# Rules for user specific configuration files,
#   User specific configuration files for applications are stored in the user's
#   home directory in a file that starts with the '.' character (a "dot file").
#   If an application needs to create more than one dot file then they should
#   be placed in a subdirectory with a name starting with a '.' character, (a
#   "dot directory"). In this case the configuration files should not start 
#   with the '.' character.
