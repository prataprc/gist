# http://finalcog.com/python-logging-root-logger-syslog
# 
# Problem:
#   We need to create multiple loggers within one application (often one per
#   module), but we need all of these to have the same behaviour (i.e.
#   use the same handlers).
# 
# Solution:
#   In the solution below, we use two handlers. Logging goes to
#   both stderr and syslog. (Linux specific example.)
# 
# Note:
#   The loggers created by logging.getLogger(X) inherit their handlers from 
#   root_logger (created with logging.getLogger()). Is this slightly surprising?

#!/usr/bin/python
 
import logging
import logging.handlers

if __name__ == '__main__':
    syslog    = logging.handlers.SysLogHandler(address='/dev/log')
    stderr    = logging.StreamHandler(open('/dev/stderr', 'w'))
    formatter = logging.Formatter(
                            '%(asctime)s %(name)s %(levelname)s %(message)s' )
    syslog.setFormatter(formatter)
    stderr.setFormatter(formatter)

    root_logger = logging.getLogger()
    root_logger.addHandler(stderr)
    root_logger.addHandler(syslog)
    root_logger.setLevel(logging.DEBUG)

    first_logger = logging.getLogger("first_logger")
    first_logger.info("foo")

    second_logger = logging.getLogger("second_logger")
    second_logger.info("bar")
