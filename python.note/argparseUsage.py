# coding: utf-8
import argparse # deprecates the optparse module

# creates an ArgumentParser object which holds all the information to parse the argument
parser = argparse.ArgumentParser(description='Process some integers.')

# return a argparse.Namespage object, return a Namespace object
# args = parser.parse_args()

# creates an integers attribute in the Namespace object
# args.integers is a list
#
#   metavar: The string shown in the help message
#   type:    The type of positional arguments
#   nargs:   Number of positional arguments.
parser.add_argument('integers', metavar='N', type=int, nargs='+', 
        help='an integer for the accumulator')

# creates a custom "accumulate" attribute in the Namespace object
#   dest:   The filed name in Namespace object.
parser.add_argument('--sum', dest='accumulate', action='store_const', 
        const=sum, default=max, help='sum the integers (default: find the max)')
# store_const: args.accumulate = const = sum
# if --sum is specified, accumulate=sum, otherwise accumulate=max

# return a argparse.Namespage object, return a Namespace object
args = parser.parse_args() # take the sys.argv as the default argument

print args.accumulate( args.integers )

# parser = argparse.ArgumentParser(prog='myprogram')
# parser.add_argument('--foo', help='foo of the %(prog)s program') # the %(prog)s format specifier
# parser.print_help()
