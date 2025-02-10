#!/bin/bash

COUNT=0
FILENAME="outfile.txt"

echo test$COUNT: /bin/ls
/bin/ls
((COUNT++))
echo

echo test$COUNT: ls
ls
((COUNT++))
echo

echo test$COUNT: /bin/cat
/bin/cat $FILENAME
((COUNT++))
echo

echo test$COUNT: cat
cat $FILENAME
((COUNT++))
echo

echo test$COUNT: echo
echo
((COUNT++))
echo

echo "test$COUNT: echo -n"
echo -n
((COUNT++))
echo

echo test$COUNT: echo Hello World
echo Hello World
((COUNT++))
echo

echo "test$COUNT: echo -n Hello World"
echo -n Hello World
((COUNT++))
echo

echo test$COUNT: 'echo "this is home $HOME of user $USER"'
echo "this is home $HOME of user $USER"
((COUNT++))
echo

echo test$COUNT: echo 'this is home $HOME of user $USER'
echo 'this is home $HOME of user $USER'
((COUNT++))
echo

echo 'test$COUNT: command ls with $?'
ls
echo $?
((COUNT++))
echo

echo 'test$COUNT: command ls with $?+$?'
ls
echo $?+$?
((COUNT++))
echo

echo 'test$COUNT: command ls asdasdasd with $?+$?'
ls asdasdasd
echo $?+$?
((COUNT++))
echo

echo "test$COUNT: 'cat -e "test1.sh" | grep -v lulz | wc -l > 'outfile.txt''"
cat -e "test1.sh" | grep -v lulz | wc -l > 'outfile.txt'
cat outfile.txt
((COUNT++))
echo

echo "test$COUNT: cat -e "test1.sh"|grep -v lulz|wc -l>'outfile.txt'"
cat -e "test1.sh"|grep -v lulz|wc -l>'outfile.txt'
cat outfile.txt
((COUNT++))
echo

