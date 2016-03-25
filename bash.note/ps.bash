# Linux-version of ps command

# ps accepts several kinds of options: UNIX options, BSD options, GNU long options. AVOID THE MIXED USE OF THESE THRESS TYPES OF OPTION.

# Process State:
#   D: uninterruptible sleep (usually IO)
#   R: running or runnable (on run queue) 
#   S: interruptible sleep (waiting for an event to complete)
#   T: stopped, either by a job control signal or because it is being tracedtraced
#   Z: defunct ("zombie") process, terminated but not reaped by its parent
# 
# More information in manual page, section PROCESS STATE CODES

# -A is equivalent to -e (for compatibility issues)
ps -A # all processes in the system


# show processes that equals to the effective user ID
ps -u root
