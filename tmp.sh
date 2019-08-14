make re
echo "\n\n"
gcc -Wall -Wextra -Werror -I includes ./srcs/* tmp.c
./a.out
