# coding: utf-8
import logging

# The logging flow of log event information is illustrated in:
#   https://docs.python.org/2/howto/logging.html#logging-flow
#
# loggers are conceptually arranged in a namespace hierarchy 
# using dots (periods) as separators
#
# logging.getLogger(__name__)

# create logger
logger = logging.getLogger('simple_example')

# set level to debug
# events of DEBUG level and above will be tracked
logger.setLevel(logging.DEBUG)

# create console handler and set hanlder's level
ch = logging.StreamHandler()
ch.setLevel(logging.DEBUG)

# create formatter
formatter = logging.Formatter('%(asctime)s - %(name)s - %(levelname)s - %(message)s')

# add formatter to handler
ch.setFormatter(formatter)

# add ch to logger
logger.addHandler(ch)

# 'application' code
logger.debug('debug message')
logger.info('info message')
logger.warn('warn message')
logger.error('error message')
logger.critical('critical message')
