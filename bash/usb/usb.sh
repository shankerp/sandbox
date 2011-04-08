#!/bin/sh
ifconfig eth0 192.168.2.101 netmask 255.255.255.0
route add default gw 192.168.2.1
echo "192.168.2.100    www.yantravideo.biz" >> /etc/hosts
echo "192.168.2.100    yantravideo.biz" >> /etc/hosts
echo "208.67.222.222" > /etc/resolv.conf
echo "208.67.220.220" >> /etc/resolv.conf
echo "202.56.250.5" >> /etc/resolv.conf
telnetd

for udi in $(/usr/bin/hal-find-by-capability --capability storage)
do
device=$(hal-get-property --udi $udi --key block.device)
    if [[ $(hal-get-property --udi $udi --key storage.bus) = "usb" ]]
    then
        printf "$device\n"
        break
    else
        echo "Failure"
        exit 0
    fi  
done

i=`echo $device | wc -c`
i=`expr $i - 1`
if [ $i != 0 ]
then
    echo "Success"
    mkdir -p /home/isense
    if [ $? -eq 0 ]
    then
        echo "Directory Creation Success"
    else
        echo "Directory Creation Failure"
    fi

    mount $device /home/isense
    echo "mount $device /home/isense"
    if [ $? -eq 0 ]
    then
        echo "Mounting Success"
        mount $device /mnt
        mkdir -p /mnt/contents/file
        mkdir -p /home/SCE01/SMP8654SDK/R3.6.0/mrua_SMP8654F_3_6_0_dev.mips/MRUA_src
        ln -s /home/isense/Thirdp/SMP8654/lib /home/SCE01/SMP8654SDK/R3.6.0/mrua_SMP8654F_3_6_0_dev.mips/MRUA_src
        cd /home/isense/iSense/bin
        source app.env
        ./loadxxx_output_itb5k_es1
        echo "800" > /proc/sys/kernel/msgmni
        cp ../../Thirdp/SMP8654/directfbrc /etc/directfbrc
        cp ../../Thirdp/SMP8654/directfbrc /root/.directfbrc
        sleep 1
        export tsskip=0
        export filetsskip=4
        export TZ=IST-5:30
        set_outports -component -f 1080i59 -digital -f HDMI_1080i59 -analog -asp 16 9 &
        export GTK_HOME=/home/isense/Thirdp/SMP8654
        cp -a $GTK_HOME/share/fonts /usr/share
        cp -a $GTK_HOME/etc/fonts /etc
        cp -a $GTK_HOME/etc/pango /etc
        cp -a $GTK_HOME/etc/gtk-2.0 /etc
        export HOME_DIR=/home/isense
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$GTK_HOME/lib:/home/isense/Thirdp/Marlin/lib:/home/isense/Thirdp/FEP/lib
        ############################################
        #           PUT APPLICATION HERE           #
        ./hal_nwalTest <nwal.txt
        ./gtkDemoApp
        ############################################
        break
    else
        echo "Mounting Failure"
        exit 0
    fi
else
    echo "Failure"
    exit 0
fi
touch /home/isense/helloworld.txt
echo "Hello World!" > /home/isense/helloworld.txt
echo "`date`" >> /home/isense/helloworld.txt
echo $device >> /home/isense/helloworld.txt
