
clear
rm libft_malloc.so
rm libft_malloc_x86_64_Darwin.so

make

echo "\nTEST 0\n"
cc -o test/test0 test/test0.c
/usr/bin/time -l ./test/test0
./run.sh /usr/bin/time -l ./test/test0
echo "\n"
echo "\nTEST 1\n"
cc -o test/test1 test/test1.c
/usr/bin/time -l ./test/test1
./run.sh /usr/bin/time -l ./test/test1
echo ".\n"
echo "\nTEST 2\n"
cc -o test/test2 test/test2.c
./run.sh /usr/bin/time -l ./test/test2
echo ".\n"
echo "\nTEST 3\n"
cc -o test/test3 test/test3.c
./run.sh ./test/test3
echo ".\n"
echo "\nTEST 3+\n"
cc -o test/test3+ test/test3+.c
./run.sh ./test/test3+
echo ".\n"
echo "\nTEST 4\n"
cc -o test/test4 test/test4.c
./run.sh ./test/test4
echo ".\n"
cc -o test/test5 test/test5.c -L. -lft_malloc
./test/test5
