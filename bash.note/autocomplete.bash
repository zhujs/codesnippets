#!/bin/bash

func1() {
    echo "You are in func1: $@"
}

func2() {
    echo "You are in func2: $@"
}

myFunc1() {
    echo "You are in myFunc1: $@"
}

#use: autocomplete "word1 word2 ..."
autocomplete() {

     # we only try to autocomplete the last word so 
     # we keep a record of the rest of the input
     OTHER_WORDS="${READLINE_LINE% *} " 

     if [[ ${#OTHER_WORDS} -ge ${#READLINE_LINE} ]]; then #if there is only 1 word...
         OTHER_WORDS="" 
     fi

     #the -W flag tells compgen to read autocomplete from the 1st argument provided
     #we then evaluate the last word of the current line through compgen
     AUTOCOMPLETE=($(compgen -W $1 "${READLINE_LINE##* }"))

     if [[ ${#AUTOCOMPLETE[@]} == 1 ]]; then #if there is only 1 match, we replace...
        READLINE_LINE="$OTHER_WORDS${AUTOCOMPLETE[0]} "
        READLINE_POINT=${#READLINE_LINE}     #we set the cursor at the end of our word
     else
        echo -e "cmd> $READLINE_LINE\n${AUTOCOMPLETE[@]}" #...else we print the possibilities
     fi
}


# here we list the values we want to allow autocompletion for
MYFUNC="func1 func2 myFunc1"

# we do this to enable line edition (man bash)
set -o emacs

#calls autocomplete when TAB is pressed
bind -x '"\t":"autocomplete \$MYFUNC"'

# -e option use the 'readline' library and store the input in the REPLY variable if no name supplied
while read -ep "cmd> "; do  
    history -s $REPLY    #set the last history command
    eval ${REPLY}
done
