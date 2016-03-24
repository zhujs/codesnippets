# coding: utf-8

# Only the name after the keyword 'import' was created, must be referenced with its full name 
import sound.effects.bb

# The 'form ... import ...' statement first tests whether the name is defined in the package (__init__.py); if not, it assumes it is a module and attempts to load it'
from sound.effects.bb import b


# When using syntax like 'import item.subitem.subsubitem', the last item can be a module or a package, but can't be a class or function or variable defined in the previous item
try:
	import souund.effects.bb.b
except ImportError as e:
	print e

# if __all__ is not defined in __init__.py, 'from package import *' does not import all submodules from the package; only name define in __init__.py will be imported, or other submodules that were explicitly loaded by previous import statements

import sound.effects.bb 
from sound.effects import *
