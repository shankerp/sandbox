filename="rgb"
a=1;
while [ 1 ]
do
b=1;
a=`expr $a + 1`;
    while [ 1 ]
    do
    echo $a;
    echo $b;
        b=`expr $b + 1`;
        ls "$filename.$b"
        if [ $? -eq 2 ]
        then
            break;
        fi
    
        cmp $a $b
        if [$? -eq 0 ]
        then
            echo "$a is same as $b"
        fi
    done
    ls "$filename.$a"
    if [ $? -eq 2 ]
    then
        break;
    fi
done

end:
echo "Over"
