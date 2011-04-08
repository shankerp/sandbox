#!/bin/bash

for DEV in /sys/block/sd*
do

#    if readlink $DEV/device | grep -q usb
    if readlink $DEV | grep -q usb
    then
        DEV=`basename $DEV`
        echo "$DEV is a USB device, info:"
#        udevinfo --query=all --name $DEV
        echo "$DEV"
        if [ -d /sys/block/${DEV}/${DEV}1 ]
        then
            device="/dev/${DEV}1"
            echo "Device is $device"
        else
            echo "Has no partitions"
        fi
        echo
    else
        echo "Failure"
    fi
done

exit 0
