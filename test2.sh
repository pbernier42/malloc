#make normal > /dev/null
#make al > /dev/null
#make > /dev/null
gcc -Wall -Werror -Wextra -I includes srcs/*.c test.c
#make fclean > /dev/null
./a.out ${1} ${2} ${3} ${4}
