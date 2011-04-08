#!/bin/bash
echo $PATH
echo $BHARATH
i686-cm-linux-gcc
ls /goo
if [ $? -ne 0 ]
then
echo "ERROR ERROR ERROR"
else
echo "GOOD GOOD GOOD"
fi

ls /home
if [ $? -ne 0 ]
then
echo "ERROR ERROR ERROR"
else
echo "GOOD GOOD GOOD"
exit 0;
fi

export HELLO="Hello Bharath!"
echo $HELLO
make
