abspath=$(cd ${0%/*} && echo $PWD/${0##*/})
path_only=`dirname "$abspath"`
ARRAY=( `find $path_only -name \*.pc` )
ARRAY_LENGTH=${#ARRAY[@]}
VAR=0
for ((  VAR = 0 ;  VAR < $ARRAY_LENGTH;  VAR+=1  ))
do
echo ${ARRAY[$VAR]}
done
