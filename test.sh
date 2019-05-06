make normal > /dev/null
make al > /dev/null
make > /dev/null
gcc -Wall -Werror -Wextra -I includes malloc.a test.c
make fclean > /dev/null
./a.out
