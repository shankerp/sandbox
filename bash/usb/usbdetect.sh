for udi in $(/usr/bin/hal-find-by-capability --capability storage)
do
device=$(hal-get-property --udi $udi --key block.device)
    if [[ $(hal-get-property --udi $udi --key storage.bus) = "usb" ]]
    then
        printf "$device\n"
    fi
done
