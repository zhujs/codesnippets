# coding: utf-8
# subprocess module intends to replace several other, older modules and functions, such as:
#    os.system
#    os.spawn*
#    os.popen*
#    popen2.*
#    commands.*


import subprocess

# Don't use arguments: stdout=PIPE or stderr=PIPE, 
# because we can not read the output of the pipe (without the Popen object)
# then child process may block
subprocess.call("echo zhu", shell=True)

# subprocess.check_call() # throw a CalledProcessError when exit with non-zero status

# subprocess.check_output() # return the output as a byte string, throw a CalledProcessError when exit with non-zero status
