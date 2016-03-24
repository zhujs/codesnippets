#! /usr/bin/env bash

# read the history file and append the contents to the history list
history -r $SCRIPT_HISTORY

# read -e : use readline library
while read -e line
do
    history -s $line # append the ARGs to the history list as a single entry
    echo $line
done

# write the current history to the history file and append them to the history list
history -w $SCRIPT_HISTORY
