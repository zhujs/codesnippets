# -*- coding: utf-8 -*-

import os
import os.path

def rm(filename):
    if os.path.isfile(filename):
        os.remove(filename)

# http://www.toptal.com/python/an-introduction-to-mocking-in-python
