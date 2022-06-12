exec="test.out"
src_files="main.c"

gcc -Wall -Wextra -o $exec $src_files

./$exec tests/01_left.txt tests/01_right.txt

rm $exec
