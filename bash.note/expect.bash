#! /usr/bin/expect

# chsh zhuj7 
# Changing the login shell for zhuj7 
# Enter the new value, or press return for the default
# 	Login Shell [/bin/bash]: 
#

# get the arguments of the script
set user [lindex $argv 0]

# spawn the chile process 
spawn chsh $user

# the command prompt to enter password
expect "word:"
# send the password
send " \r"

# expect -re "\[(.*)]:" ==> using REs
# expect_out(1, string) gets the first group, expect_out( 1, start ) returns the start index of the first group
#
# expect -re "\[(.*)]:" 
#if { $expect_out(1,string)!="/bin/tcsh"} {
#	send "/bin/tcsh" 
#}

expect "]:"
send "\r"

expect eof
exit


#! /usr/bin/expect

# Prompt function with timeout and default

# set prompt [lindex $argv 0]
# set def [lindex $argv 1]
# set response $def
# set tout [lindex $argv 2]
# 
# send_tty "$prompt: "
# 
# set timeout $tout
# 
# # check the 'expect' command usage format
# expect "\n" {
# 	set raw $expect_out(buffer)
# 	# remove final carriage return
# 	set response [string trimright "$raw" "\n"]
# }
# 
# # if expression is the syntax of Tcl language
# if {"$response" == ""} {set response $def}
# send "$response"
