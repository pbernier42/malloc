
echo "TMP FREE\n"
cc -o testfree srcs/tmpfree.c
./run.sh /usr/bin/time -l ./testfree
echo "\n"
