# coding: utf-8
try:
    testList = [ 'a', 'b' ]
    int( testList[3] )
except ValueError, IndexError:
    # Wrong syntax to catch multi-exceptions, it won't catch IndexError
    # Instead, it means that the exception object will be saved as IndexError
    pass
finally:
    # the saved IndexError exception will be re-raised unless the finally clause raises another exception or executes a 'return' or 'break' statement.
    pass

# proper syntax to catch multi-exceptions
#try:
#    testList = [ 'a', 'b' ]
#    int( testList[3] )
#except ( ValueError, IndexError ) as e:
# python 3 wiil del the target variable e after the except clause for saving the memory
#    pass
