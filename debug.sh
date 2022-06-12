exec="debug.out"
src_files="main.c"

gcc -Wall -Wextra -g -o $exec $src_files
if [ $? != 0 ]
then
    exit 1
fi

gdb --args ./$exec tests/01_left.txt tests/01_right.txt

rm $exec
