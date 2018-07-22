#! /usr/bin/env python

import getopt, sys
from optparse import OptionParser

print sys.argv[0]
# Process the command line
cmd_options = getopt.getopt(sys.argv[1:], "s:p:x:ct:ih")

# Take the default from the environment variables, if set
print cmd_options
for opt in cmd_options[0] :
    print opt

print "---"

optParser = OptionParser(usage="helo")
optParser.add_option("--seed", dest="user_seed", default="0",
                    help="Seed to use for random generators")
optParser.add_option("-s", dest="sgeseed", default="0",
                    help="Seed to use for sge")
(options, args) = optParser.parse_args()
