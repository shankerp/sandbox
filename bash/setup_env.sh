if ! [ -z "$BUILD_ROOT" ]; then
    echo ""
    echo "##################################################################"
    echo "Whoa! Sodaville toolchain is already available for this terminal!!"
    echo "##################################################################"
    echo ""
else
    # User specific environment and startup programs
    export BUILD_ROOT='/home/sodaville/IntelCE-18.200463/'
    export BUILD_DIR=build_i686/staging_dir/
    export BUILD_DEST=$BUILD_ROOT/$BUILD_DIR
    export FSROOT=$BUILD_ROOT/project_build_i686/IntelCE/root
    
    export PATH=/bin:/usr/bin:$PATH:$BUILD_ROOT/build_i686/staging_dir/bin
    
    #########  Modified for Cross Compiler Environment ###########
    export PLATFORM='/home/sodaville/IntelCE-18.200463/'
    export MAKETOP=$PLATFORM/build_i686/staging_dir
    export CROSS_C_ROOT_PATH=$PLATFORM/build_i686/staging_dir
    # export SCCTOP=$MAKETOP/usr/src/scc
    
    # export AM3_GCC_DEFAULT_OPTIONS="-mam33-2 --sysroot=${CROSS_C_ROOT_PATH}"
    export AM3_GCC_DEFAULT_OPTIONS="--sysroot=${CROSS_C_ROOT_PATH}"
    
    #if test ${PATH} == ${PATH//canmore/XXX} ; then
    #PATH=${PLATFORM}/i686-linux-elf/bin/:${PATH}
    #fi
    ##############################################################
    
    export PATH
    unset USERNAME
    
    echo "*** Setup Env ***"
    echo "PLATFORM                = " ${PLATFORM}
    echo "MAKETOP                 = " ${MAKETOP}
    echo "CROSS_C_ROOT_PATH       = " ${CROSS_C_ROOT_PATH}
    echo "AM3_GCC_DEFAULT_OPTIONS = " ${AM3_GCC_DEFAULT_OPTIONS}
    echo "PATH = " ${PATH}
fi
