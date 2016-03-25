#!/bin/bash
set -o errexit # Exit immediately if a command exits with a non-zero status.
set -o noclobber
set -o nounset
set -o pipefail    

set -o errtrace # ERR is inherited by shell functions

function traperr
{
	echo "ERROR: ${BASH_SOURCE[0]}"
	echo "PROCESS ID: $$"
}

# ERR：命令退出状态不为0时，其相应的命令被执行
trap traperr ERR

echo "BEGIN"

cat /etc/passwd | while read aLine
do
	# in a subshell
    # -o errtrace : ERR is inherited by subshell
    # -o errexit : exit on error 
    # traperr will be invoked twice (subshell and current shell)
    test=$(true | false);
done


echo "END"
exit 0
