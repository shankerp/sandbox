export ISENSE_THIRDP_BUILD_ROOT=/home/sodaville/IntelCE-18.200463/build_i686
export ISENSE_THIRDP_SYSTEM=/home/isense/CE4200
export ISENSE_THIRDP_BUILD_SDK_PATH=$ISENSE_THIRDP_BUILD_ROOT/i686-linux-elf
export ISENSE_THIRDP_BUILD_ROOT_PKG_CONFIG=$ISENSE_THIRDP_BUILD_SDK_PATH/usr/local/lib/pkgconfig
export ISENSE_THIRDP_INSTALL_PATH=$ISENSE_THIRDP_SYSTEM/Thirdp/CE4200
export PKG_CONFIG_PATH=$ISENSE_THIRDP_INSTALL_PATH/lib/pkgconfig:$ISENSE_THIRDP_BUILD_ROOT_PKG_CONFIG
export LD_LIBRARY_PATH=/home/isense/CE4200/Thirdp/CE4200/lib
i686-cm-linux-gcc gtkkeys.c `pkg-config --cflags --libs gtk+-2.0` -ltiff  -lpangoft2-1.0  -lpixman-1 -lfontconfig  -liconv -lxml2
cp -v a.out /home/sodaville/IntelCE-18.200463/project_build_i686/IntelCE/root/iSense/bin/gtkkeys.out
cp -v a.out $ISENSE_THIRDP_INSTALL_PATH/bin/gtkkeys.out
unset LD_LIBRARY_PATH ISENSE_THIRDP_BUILD_SDK_PATH ISENSE_THIRDP_BUILD_ROOT ISENSE_THIRDP_BUILD_ROOT_PKG_CONFIG ISENSE_THIRDP_INSTALL_PATH PKG_CONFIG_PATH ISENSE_THIRDP_SYSTEM
