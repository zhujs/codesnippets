# coding: utf-8
# python warnings.py
# python -W "ignore:do not:UserWarning::0" warnings.py

import warnings

# Warning is subclass of Exception in Python
def warnDeprecated():
    warnings.warn('WARN: deprecated function')

# register a filter for 'warning messages'
# warnings.filterwarnings('ignore', '.*do not.*',)

# throw an exception for 'UserWarning'
warnings.simplefilter('error', UserWarning)


# how to deliver warning messages
#
# save_showwarning = warnings.showwarning
# warnings.showwarning = function_to_use

# how to format warning messages
#
# save_formatwaring = warnings.formatwarning
# warnings.formatwarning = function_to_use
warnDeprecated()
print "Warnings examples."
