#make normal > /dev/null
#make al > /dev/null
#make > /dev/null
gcc -Wall -Werror -Wextra -I ../includes ../srcs/*.c test_all.c
#make fclean > /dev/null
./a.out cul
