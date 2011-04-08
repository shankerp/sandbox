#!/bin/bash

function get_package_info()
{
    package=$1;
    value=`echo $package | awk -F".tar.*|.zip" '{print $1}'`;
    dirvalue=`echo $package | awk ' { print match($0, ".tar.*|.zip") }'`;
    if [ $dirvalue -eq 0 ]
    then
        echo "$value is a src"
    else
        echo "$value is a package"
    fi
}

get_package_info gtk+;
#value=$(strip_archive_format);
#echo $value;
