#!/bin/sh
abspath=$(cd ${0%/*} && echo $PWD/${0##*/})
path_only=`dirname "$abspath"`
sed -i.bak "
/prefix=\// c\
prefix=${path_only}
" $1

