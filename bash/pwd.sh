#!/bin/bash
#==========================
# bash - find path to script
#==========================
abspath=$(cd ${0%/*} && echo $PWD/${0##*/})

# to get the path only - not the script name - add
    path_only=`dirname "$abspath"`

#display the paths to prove it works
    echo $BASH_SOURCE
    echo `dirname "$BASH_SOURCE"`
    echo $abspath
    echo $path_only
