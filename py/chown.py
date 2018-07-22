#! /usr/bin/env python

import os

rc = os.system( 'touch a' )
print rc
rc = os.system( 'sudo touch /a' )
rc = os.system( 'sudo touch /b' )
rc = os.system( 'sudo touch /c' )
print rc
