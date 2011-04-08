#!/bin/bash

function returnString()
{
    echo "$@"
}

function formatBuildTime()
{
buildTime=$1;
buildHours=`expr \( $buildTime \/ 3600 \)`;
buildMins=`expr \( \( $buildTime - \( $buildHours \* 3600 \) \) \/ 60 \)`;
buildSecs=`expr \( \( $buildTime - \( $buildHours \* 3600 \) \) - \( $buildMins \* 60 \) \)`;

if [ $buildHours -gt 0 ]
then
    echo "$buildHours\h:$buildMins\m:$buildSecs\s"
else
    echo "${buildMins}m:$buildSecs s"
fi
}

starttime=`date +%s`
echo "Shell Script To Get User Input";

while read inputline
do
what="$inputline"
echo $what;

if [ -z "${what}" ];
then
endtime=`date +%s`;
timetaken=`expr $endtime - $starttime`;
buildTime=$(formatBuildTime `expr $endtime - $starttime`);
echo "Time taken to build:"
echo "--------------------"
echo $buildTime
exit
fi

done
