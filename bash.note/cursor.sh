# Cursor Movement using escape sequences, <L>, <C>, <N> should be replaced with numbers, `tput` is the encouraged way to send the escape sequences
# More infomation about escape sequence:
#   https://en.wikipedia.org/wiki/ANSI_escape_code
#
# Puts the cursor at line L and column C.
#   \033[<L>;<C>H Or \033[<L>;<C>f
# Move the cursor up N lines:
#   \033[<N>A
# Move the cursor down N lines:
#   \033[<N>B
# Move the cursor forward N columns:
#   \033[<N>C
# Move the cursor backward N columns:
#   \033[<N>D
#
# Clear the screen, move to (0,0):
#   \033[2J
# Erase to end of line:
#   \033[K
# Save cursor position:
#   \033[s
# Restore cursor position:
#   \033[u

# moveCursor ROW COL: mvoe cursor to specific coordinate 
function moveCursor() {
    echo -ne "\[\033[${1};${2}H\]"
}

i=0
while true
do
    tput sc # echo -ne "\033[s" 
    echo $i
    sleep 2
    echo -ne "First line\nSecond line\nThird Line"
    sleep 2
    tput rc # echo -ne "\033[u" 
    tput ed # 清除光标到设备末尾的数据（Mac OS下失效）
    ((i++)) 
done
