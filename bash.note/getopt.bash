#!/bin/bash

# A small example program for using the new getopt(1) program.
# This program will only work with bash(1)
# An similar program using the tcsh(1) script language can be found
# as parse.tcsh

# Note that we use `"$@"' to let each command-line parameter expand to a 
# separate word. The quotes around `$@' are essential!
# We need TEMP as the `eval set --' would nuke the return value of getopt.

# In this example, option 'b' requires an argument and option 'c' takes an
# optional arg, the getopt(3) function only handles short options, but the
# getopt(1) command handles both short and long options

# '-' in the optstring means arguments are in the order as their input
# getopt -o -ab:c:: -- -a hello -b world 'kidding you'
# ouput: -a 'hello' -b 'world' 'kidding you' --

# '+' in the optstring means scaning process stops once it meets an 
# non-option argument
# getopt -o +ab:c:: -- -a hello -b world 'kidding you'
# -a -- 'hello' '-b' 'world' 'kidding you'

# in default situation, arguments will be shuffled
# getopt -o ab:c:: -- -a hello -b world 'kidding you'
# output: -a -b 'world' -- 'hello' 'kidding you'
TEMP=`getopt -o ab:c:: --long a-long,b-long:,c-long:: \
     -n 'example.bash' -- "$@"`

if [ $? != 0 ] ; then echo "Terminating..." >&2 ; exit 1 ; fi

# Note the quotes around `$TEMP': they are essential!
# Note the differences between following command
# If TEMP="'a    b'", 
# `eval set -- "$TEMP"` expands to `eval set -- 'a    b'`
# `eval set -- $TEMP` expands to `eval set -- a b`
eval set -- "$TEMP"

while true ; do
	case "$1" in
		-a|--a-long) echo "Option a" ; shift ;;
		-b|--b-long) echo "Option b, argument \`$2'" ; shift 2 ;;
		-c|--c-long) 
			# c has an optional argument. As we are in quoted mode,
			# an empty parameter will be generated if its optional
			# argument is not found. In unquoted mode nothing will 
            # be generated
			case "$2" in
				"") echo "Option c, no argument"; shift 2 ;;
				*)  echo "Option c, argument \`$2'" ; shift 2 ;;
			esac ;;
		--) shift ; break ;;
		*) echo "Internal error!" ; exit 1 ;;
	esac
done
echo "Remaining arguments:"
for arg do echo '--> '"\`$arg'" ; done
