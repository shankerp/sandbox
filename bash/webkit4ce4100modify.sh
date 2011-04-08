#########################################################
#
# iSense Webkit Package Cross Compiler
#
########################################################

###########################################################
########## Ideal Custom Modification begins here ##########
###########################################################

#Canmore related variables - From canmore setup_env.sh

#########################################################################################
#To be modified as per user needs
#########################################################################################
#SDK path where Intel SDK is untarred.
export ISENSE_THIRDP_SDK_HOME=/home/sodaville/IntelCE-18.200463/

#Directory where WebKit shared Object Library is to be stored in the current platform
export ISENSE_PLATFORM_SOURCE=/home/bharath/workspace/adcom/src/

# Directory where the third party source code and packages are located
export ISENSE_THIRDP_PATH=/home/bharath/workspace/mvista/thirdp_ce4200/

#SDK BUILD Path
exportAndPrintOutput ISENSE_THIRDP_BUILD_ROOT=$ISENSE_THIRDP_SDK_HOME/build_i686
exportAndPrintOutput PLATFORM=$ISENSE_THIRDP_SDK_HOME/build_i686

# Directory where build targets are installed
exportAndPrintOutput ISENSE_THIRDP_SYSTEM=/home/isense/CE4200

# Directory where temporary build targets are installed (for libicu)
exportAndPrintOutput ISENSE_THIRDP_TMP_BUILD_PATH=/tmp

###########################################################
########## Ideal Custom Modification ends here ##########
###########################################################
#########################################################################################
    

exportedVariablesList=( )

#=======================================================================================#
#FUNCTIONS                                                                              #
#=======================================================================================#
function parse_single_arg()
{
    LOCAL_VAR=0
    RET_VAL=0
    for ((  LOCAL_VAR = 0 ;  LOCAL_VAR < ARGC;  LOCAL_VAR+=1  ))
    do
        if [ ${ARGV[$LOCAL_VAR]} == $1 ]
        then
            RET_VAL=1
            break
        fi
    done
    return $RET_VAL;
}

function parse_args()
{
    LOC_VAR=0
    RET_VALU=0
    args=("$@")

    for (( LOC_VAR = 0; LOC_VAR < $#; LOC_VAR+=1 ))
    do
        parse_single_arg ${args[LOC_VAR]}
        if [ $? -eq 1 ]
        then
            RET_VALU=1
            break
        fi
    done
    return $RET_VALU;
}

function exportAndPrintOutput()
{
    unset $1;
    export $1="$2"
    eval "envvar=\$$1"
    echo "$1=$envvar"
    exportedVariablesList=( "${exportedVariablesList[@]}" "$1" )
}

function printExportedVariables()
{
    for (( i = 0; i < ${#exportedVariablesList[@]}; i++ ))
    do
        eval "envvar=\$${exportedVariablesList[i]}"
        echo "${exportedVariablesList[i]}=$envvar";
    done
}

function install_build_deps()
{
    sudo apt-get install -y build-essential automake autoconf libtool m4 flex gperf bison gettext libglib2.0-dev libfreetype6 libfreetype6-dev libx11-dev libxpm-dev x11proto-xext-dev libxext-dev libgpg-error-dev binutils-gold libgtk2.0-dev libicu-dev libncurses-dev dos2unix doxygen gtk-doc-tools
}

function prepare_environment()
{
    exportAndPrintOutput MAKETOP=$PLATFORM/i686-linux-elf
    exportAndPrintOutput CROSS_C_ROOT_PATH=$PLATFORM/i686-linux-elf
    exportAndPrintOutput AM3_GCC_DEFAULT_OPTIONS="--sysroot=${CROSS_C_ROOT_PATH}"
    exportAndPrintOutput KBUILD_NOPEDANTIC=1

    exportAndPrintOutput ISENSE_THIRDP_PACKAGES_PATH=$ISENSE_THIRDP_PATH/packages
    exportAndPrintOutput ISENSE_THIRDP_SRC_PATH=$ISENSE_THIRDP_PATH/src
    exportAndPrintOutput ISENSE_THIRDP_INSTALL_PATH=$ISENSE_THIRDP_SYSTEM/Thirdp/CE4200
    exportAndPrintOutput ISENSE_THIRDP_HOST_ARCH=`gcc -dumpmachine`
    exportAndPrintOutput ISENSE_THIRDP_TARGET_ARCH=i686-cm-linux
    exportAndPrintOutput ISENSE_THIRDP_BUILD_SDK_PATH=$ISENSE_THIRDP_BUILD_ROOT/i686-linux-elf
    exportAndPrintOutput ISENSE_THIRDP_BUILD_ROOT_PKG_CONFIG=$ISENSE_THIRDP_BUILD_SDK_PATH/usr/local/lib/pkgconfig
    exportAndPrintOutput ISENSE_THIRDP_ORIG_LD_LIBRARY_PATH=$LD_LIBRARY_PATH
    # Speed up by making multiple parallel builds
    exportAndPrintOutput AM_MAKEFLAGS="-j10"

    ## Following are expected to be common for all platforms
    mkdir -p $ISENSE_THIRDP_INSTALL_PATH/lib $ISENSE_THIRDP_INSTALL_PATH/lib/pkgconfig $ISENSE_THIRDP_INSTALL_PATH/bin $ISENSE_THIRDP_INSTALL_PATH/sbin $ISENSE_THIRDP_INSTALL_PATH/include $ISENSE_THIRDP_INSTALL_PATH/share $ISENSE_THIRDP_INSTALL_PATH/man $ISENSE_THIRDP_INSTALL_PATH/man/man1

    if [ $ISENSE_THIRDP_BUILD_SDK_PATH ]
    then
        ISENSE_THIRDP_SDK_LDFLAGS="-L$ISENSE_THIRDP_BUILD_SDK_PATH/usr/lib -L$ISENSE_THIRDP_BUILD_SDK_PATH/usr/local/lib "
        ISENSE_THIRDP_SDK_LD_LIBRARY_PATH=":$ISENSE_THIRDP_BUILD_SDK_PATH/usr/lib:$ISENSE_THIRDP_BUILD_SDK_PATH/usr/local/lib"
        ISENSE_THIRDP_SDK_COMPILER="$ISENSE_THIRDP_BUILD_SDK_PATH/bin/"
    else
        ISENSE_THIRDP_SDK_LDFLAGS="";
        ISENSE_THIRDP_SDK_LD_LIBRARY_PATH="";
        ISENSE_THIRDP_SDK_COMPILER=""
    fi
    exportAndPrintOutput LDFLAGS="-L$ISENSE_THIRDP_INSTALL_PATH/lib $ISENSE_THIRDP_SDK_LDFLAGS"
    exportAndPrintOutput LD_LIBRARY_PATH=$ISENSE_THIRDP_INSTALL_PATH/lib$ISENSE_THIRDP_SDK_LD_LIBRARY_PATH
    exportAndPrintOutput CC=$ISENSE_THIRDP_SDK_COMPILER$ISENSE_THIRDP_TARGET_ARCH-gcc
    exportAndPrintOutput CXX=$ISENSE_THIRDP_SDK_COMPILER$ISENSE_THIRDP_TARGET_ARCH-g++
    exportAndPrintOutput AR=$ISENSE_THIRDP_SDK_COMPILER$ISENSE_THIRDP_TARGET_ARCH-ar
    exportAndPrintOutput RANLIB=$ISENSE_THIRDP_SDK_COMPILER$ISENSE_THIRDP_TARGET_ARCH-ranlib
    exportAndPrintOutput LD=$ISENSE_THIRDP_SDK_COMPILER$ISENSE_THIRDP_TARGET_ARCH-ld
#    exportAndPrintOutput M4=$ISENSE_THIRDP_SDK_COMPILER$ISENSE_THIRDP_TARGET_ARCH-m4
    exportAndPrintOutput NM=$ISENSE_THIRDP_SDK_COMPILER$ISENSE_THIRDP_TARGET_ARCH-nm
#    exportAndPrintOutput BISON=$ISENSE_THIRDP_SDK_COMPILER$ISENSE_THIRDP_TARGET_ARCH-bison
    exportAndPrintOutput STRIP=$ISENSE_THIRDP_SDK_COMPILER$ISENSE_THIRDP_TARGET_ARCH-strip
    exportAndPrintOutput CXXFLAGS="-DISENSE_BUILD_CANMORE -DISENSE_SUPPORT_IR -I$ISENSE_THIRDP_INSTALL_PATH/include -I$ISENSE_THIRDP_BUILD_SDK_PATH/include -I$ISENSE_THIRDP_BUILD_SDK_PATH/usr/local/include -g "
    exportAndPrintOutput CPPFLAGS=$CXXFLAGS
    exportAndPrintOutput CFLAGS=$CXXFLAGS
    exportAndPrintOutput PKG_CONFIG_PATH=$ISENSE_THIRDP_INSTALL_PATH/lib/pkgconfig:$ISENSE_THIRDP_BUILD_ROOT_PKG_CONFIG
    exportAndPrintOutput ISENSE_THIRDP_BUILD_COMMON_CONFIG="--host=$ISENSE_THIRDP_TARGET_ARCH --prefix=$ISENSE_THIRDP_INSTALL_PATH"
    exportAndPrintOutput ISENSE_THIRDP_CC=$CC
    exportAndPrintOutput ISENSE_THIRDP_CXX=$CXX
    exportAndPrintOutput ISENSE_THIRDP_AR=$AR
    exportAndPrintOutput ISENSE_THIRDP_RANLIB=$RANLIB
    exportAndPrintOutput ISENSE_THIRDP_LD=$LD
    #exportAndPrintOutput ISENSE_THIRDP_M4=$M4
    exportAndPrintOutput ISENSE_THIRDP_NM=$NM
    #exportAndPrintOutput ISENSE_THIRDP_BISON=$BISON
    exportAndPrintOutput ISENSE_THIRDP_STRIP=$STRIP
    exportAndPrintOutput ISENSE_THIRDP_CXXFLAGS=$CXXFLAGS
    exportAndPrintOutput ISENSE_THIRDP_CPPFLAGS=$CPPFLAGS
    exportAndPrintOutput ISENSE_THIRDP_CFLAGS=$CFLAGS
}

function prepare_packages_list()
{
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_JPEG=jpeg-6b.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_ICONV=libiconv-1.13.1.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_TIFF=tiff-3.7.4.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_ZLIB=zlib-1.2.3.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_PNG=libpng-1.2.29.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_GLIB=glib-2.24.1.tar.bz2
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_XML2=libxml2-2.7.7.tar.bz2
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_ATK=atk-1.32.0.tar.bz2
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_FREETYPE=freetype-2.4.4.tar.bz2
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_EXPAT=expat-2.0.1.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_FONTCONFIG=fontconfig-2.4.91.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_PIXMAN=pixman-0.18.3.tar.bz2
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_CAIRO=cairo-1.10.2.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_POPT=popt-1.10.2.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_PANGO=pango-1.28.3.tar.bz2
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_GTK=gtk+
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_GPERF=gperf-3.0.3.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_ICU=icu4c-4_4_1-src.tgz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_LIBGPGERROR=libgpg-error-1.7.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_LIBGCRYPT=libgcrypt-1.4.5.tar.bz2
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_GNUTLS=gnutls-2.8.5.tar.bz2
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_SQLITE=sqlite-3.6.8
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_LIBSOUP=libsoup-2.31.90.tbz2
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_LIBUNGIF=libungif-4.1.4.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_ENCHANT=enchant-1.1.6.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_LIBXSLT=libxslt-1.1.9.tar.gz
    exportAndPrintOutput ISENSE_THIRDP_PACKAGE_WEBKIT=webkit-1.2.0
}

ISENSE_THIRDP_VARIABLE=`env | grep ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR | wc -c`
ISENSE_THIRDP_VARIABLE=`expr $ISENSE_THIRDP_VARIABLE - 1`
if [ $ISENSE_THIRDP_VARIABLE -le 0 ]
then
    exportAndPrintOutput ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR=0
    echo "ISENSE WEBKIT CROSS COMPILE"
    echo "==========================="
    echo "Exported ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR = 0"
else
    echo "ISENSE WEBKIT CROSS COMPILE"
    echo "==========================="
    echo "Packages built so far = $ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR"
fi


exportAndPrintOutput ISENSE_THIRDP_DIR_JPEG=$ISENSE_THIRDP_PACKAGES_PATH/jpeg/src
exportAndPrintOutput ISENSE_THIRDP_DIR_ICONV=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_ICONV
exportAndPrintOutput ISENSE_THIRDP_DIR_TIFF=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_TIFF
exportAndPrintOutput ISENSE_THIRDP_DIR_ZLIB=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_ZLIB
exportAndPrintOutput ISENSE_THIRDP_DIR_PNG=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_PNG
exportAndPrintOutput ISENSE_THIRDP_DIR_GLIB=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_GLIB
exportAndPrintOutput ISENSE_THIRDP_DIR_XML2=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_XML2
exportAndPrintOutput ISENSE_THIRDP_DIR_ATK=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_ATK
exportAndPrintOutput ISENSE_THIRDP_DIR_FREETYPE=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_FREETYPE
exportAndPrintOutput ISENSE_THIRDP_DIR_EXPAT=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_EXPAT
exportAndPrintOutput ISENSE_THIRDP_DIR_FONTCONFIG=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_FONTCONFIG
exportAndPrintOutput ISENSE_THIRDP_DIR_PIXMAN=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_PIXMAN
exportAndPrintOutput ISENSE_THIRDP_DIR_CAIRO=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_CAIRO
exportAndPrintOutput ISENSE_THIRDP_DIR_POPT=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_POPT
exportAndPrintOutput ISENSE_THIRDP_DIR_PANGO=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_PANGO
exportAndPrintOutput ISENSE_THIRDP_DIR_GTK=$ISENSE_THIRDP_SRC_PATH/$ISENSE_THIRDP_PACKAGE_VER_GTK
exportAndPrintOutput ISENSE_THIRDP_DIR_GPERF=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_GPERF
exportAndPrintOutput ISENSE_THIRDP_DIR_ICU=$ISENSE_THIRDP_PACKAGES_PATH/icu/source
exportAndPrintOutput ISENSE_THIRDP_DIR_LIBGPGERROR=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_LIBGPGERROR
exportAndPrintOutput ISENSE_THIRDP_DIR_LIBGCRYPT=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_LIBGCRYPT
exportAndPrintOutput ISENSE_THIRDP_DIR_GNUTLS=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_GNUTLS
exportAndPrintOutput ISENSE_THIRDP_DIR_SQLITE=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_SQLITE
exportAndPrintOutput ISENSE_THIRDP_DIR_LIBSOUP=$ISENSE_THIRDP_SRC_PATH/$ISENSE_THIRDP_PACKAGE_VER_LIBSOUP
exportAndPrintOutput ISENSE_THIRDP_DIR_LIBUNGIF=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_LIBUNGIF
exportAndPrintOutput ISENSE_THIRDP_DIR_ENCHANT=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_ENCHANT
exportAndPrintOutput ISENSE_THIRDP_DIR_LIBXSLT=$ISENSE_THIRDP_PACKAGES_PATH/$ISENSE_THIRDP_PACKAGE_VER_LIBXSLT
exportAndPrintOutput ISENSE_THIRDP_DIR_WEBKIT=$ISENSE_THIRDP_SRC_PATH/$ISENSE_THIRDP_PACKAGE_VER_WEBKIT

exportAndPrintOutput ISENSE_THIRDP_BUILD_JPEG_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --enable-shared"
exportAndPrintOutput ISENSE_THIRDP_BUILD_ICONV_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG"
exportAndPrintOutput ISENSE_THIRDP_BUILD_TIFF_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --without-x --enable-shared --disable-static"
exportAndPrintOutput ISENSE_THIRDP_BUILD_ZLIB_CONFIG="--prefix=$ISENSE_THIRDP_INSTALL_PATH --shared"
exportAndPrintOutput ISENSE_THIRDP_BUILD_PNG_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --disable-static"
exportAndPrintOutput ISENSE_THIRDP_BUILD_GLIB_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --with-libiconv=gnu --enable-debug=yes --enable-tls"

#-- GLIB Config Note --
#The following command is giving problems. But using the above command without
#LDFLAGS and CPP FLAGS could build successfully. If this is necessary we can
#add by exporting LDFLAGS and CPP FLAGS in the for loop for count 15
#exportAndPrintOutput ISENSE_THIRDP_BUILD_GLIB_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --with-libiconv=gnu --enable-debug=yes CPPFLAGS=\"-I$ISENSE_THIRDP_INSTALL_PATH/include\" LDFLAGS=\"-L$ISENSE_THIRDP_INSTALL_PATH/lib\""
#-- END GLIB Config Note --

#-- XML Config Note --
#Please check whether --with-zlib[=DIR] is required.
#Canmore document recommends using --without-thread --without-python, though building without that didn't lead to any issues. Need to check the same.
#If python is not installed in $ISENSE_HOST_ARCH system, consider using --without-python
#-- END XML Config Note --
exportAndPrintOutput ISENSE_THIRDP_BUILD_XML_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --without-thread --without-python --disable-static"
exportAndPrintOutput ISENSE_THIRDP_BUILD_ATK_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --disable-static"
exportAndPrintOutput ISENSE_THIRDP_BUILD_FREE_TYPE_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --disable-static"
exportAndPrintOutput ISENSE_THIRDP_BUILD_EXPAT_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG"
#-- Font Config Note --
#Please consider using --without-x --enable-directfb --disable-xlib --disable-win32 --with-arch=$ISENSE_TARGET_ARCH
#-- END Font Config Note --

exportAndPrintOutput ISENSE_THIRDP_BUILD_FONTCONFIG_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --enable-libxml2 --disable-docs --without-x --enable-directfb --disable-xlib --disable-win32"
#Pixman Config Note:
#Please consider using --without-x
#END Pixman Config Note
exportAndPrintOutput ISENSE_THIRDP_BUILD_PIXMAN_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --disable-gtk --disable-static --without-x"
exportAndPrintOutput ISENSE_THIRDP_BUILD_CAIRO_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --disable-xlib --disable-xlib-xrender --enable-directfb=yes --enable-ft=yes --without-x --disable-test-surfaces --disable-svg --disable-win32 --disable-static --disable-xcb"
exportAndPrintOutput ISENSE_THIRDP_BUILD_POPT_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG"
exportAndPrintOutput ISENSE_THIRDP_BUILD_PANGO_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --disable-static --without-x"
exportAndPrintOutput ISENSE_THIRDP_BUILD_GTK_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --disable-static --with-gdktarget=directfb --disable-glibtest --without-x --without-xinput --disable-xinerama --disable-xkb --disable-cups"
exportAndPrintOutput ISENSE_THIRDP_BUILD_GPERF_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG"
exportAndPrintOutput ISENSE_THIRDP_BUILD_HOST_ICU_CONFIG=""
exportAndPrintOutput ISENSE_THIRDP_BUILD_ICU_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --with-cross-build=$ISENSE_THIRDP_TMP_BUILD_PATH/icu/source"
exportAndPrintOutput ISENSE_THIRDP_BUILD_LIBGPGERROR_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG"
exportAndPrintOutput ISENSE_THIRDP_BUILD_LIBGCRYPT_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --disable-asm --with-gpg-error-prefix=$ISENSE_THIRDP_INSTALL_PATH"
exportAndPrintOutput ISENSE_THIRDP_BUILD_GNUTLS_CONFIG="--prefix=$ISENSE_THIRDP_INSTALL_PATH --with-libgcrypt-prefix=$ISENSE_THIRDP_INSTALL_PATH --enable-shared --disable-static"
exportAndPrintOutput ISENSE_THIRDP_BUILD_SQLITE_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --disable-tcl --disable-readline"
exportAndPrintOutput ISENSE_THIRDP_BUILD_LIBSOUP_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --without-gnome --with-libgcrypt-prefix=$ISENSE_THIRDP_INSTALL_PATH"
exportAndPrintOutput ISENSE_THIRDP_BUILD_LIBUNGIF_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --enable-shared --with-x=no --enable-directfb=yes --enable-xlib=no"
exportAndPrintOutput ISENSE_THIRDP_BUILD_ENCHANT_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG"
exportAndPrintOutput ISENSE_THIRDP_BUILD_LIBXSLT_CONFIG="$ISENSE_THIRDP_BUILD_COMMON_CONFIG --without-crypto --enable-shared --with-libxml-prefix=$ISENSE_THIRDP_INSTALL_PATH"
exportAndPrintOutput ISENSE_THIRDP_BUILD_WEBKIT_CONFIG="WebKitTools/Scripts/build-webkit --gtk --bml --with-isense --no-svg --no-geolocation --no-video $ISENSE_THIRDP_BUILD_COMMON_CONFIG --enable-shared --with-target=directfb --disable-video --disable-optimizations"

###########################################################################################
# Calculates build time in terms of hours, minutes and seconds
# WARNING: DO NOT ADD ANY OTHER PRINTS (ECHO) INSIDE THIS FUNCTION
###########################################################################################
function formatBuildTime()
{
# WARNING: DO NOT ADD ANY OTHER PRINTS (ECHO) INSIDE THIS FUNCTION
    buildTime=$1;
    buildHours=`expr \( $buildTime \/ 3600 \)`;
    buildMins=`expr \( \( $buildTime - \( $buildHours \* 3600 \) \) \/ 60 \)`;
    buildSecs=`expr \( \( $buildTime - \( $buildHours \* 3600 \) \) - \( $buildMins \* 60 \) \)`;

# WARNING: DO NOT ADD ANY OTHER PRINTS (ECHO) INSIDE THIS FUNCTION
    if [ $buildHours -gt 0 ]
        then
            echo "${buildHours}h:${buildMins}m:${buildSecs}s"
    else
        echo "${buildMins}m:${buildSecs}s"
            fi
# WARNING: DO NOT ADD ANY OTHER PRINTS (ECHO) INSIDE THIS FUNCTION
}

###########################################################################################
# Configure and build packages
# This function acceps three parameters in the following order
# 1 - Package tar name
# 2 - Directory where the configure file will be present after the tar file is extracted
# 3 - Configure command line arguments
###########################################################################################
function isense_config_and_build()
{
    ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE=$1;
    ISENSE_THIRDP_CONFIG_AND_BUILD_DIR=$2;
    ISENSE_THIRDP_CONFIG_AND_BUILD_CONFIG=$3;

    cd $ISENSE_THIRDP_PACKAGES_PATH;
    if [ $? -eq 0 ]
    then
        echo "ISENSE WEBKIT CROSS COMPILE"
        echo "==========================="
        echo "Extracting $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE"
        if [ $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE != $ISENSE_THIRDP_PACKAGE_GTK ] && [ $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE != $ISENSE_THIRDP_PACKAGE_LIBSOUP ]
        then
            rm -fr $ISENSE_THIRDP_CONFIG_AND_BUILD_DIR;
            tar -xf $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE;
        fi
        if [ $? -eq 0 ] || [ $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE == $ISENSE_THIRDP_PACKAGE_EXPAT ]
        then
            echo "ISENSE WEBKIT CROSS COMPILE"
            echo "==========================="
            echo "Entering directory : $ISENSE_THIRDP_CONFIG_AND_BUILD_DIR"
            cd $ISENSE_THIRDP_CONFIG_AND_BUILD_DIR;
            if [ $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE == $ISENSE_THIRDP_PACKAGE_JPEG ]
            then
                # Fix for ancient libtool stuff
                echo "Replacing config.sub and config.guess from host's libtool/config"
                if [ "$USER" == "root" ]
                then
		            cp -f /usr/share/libtool/config/config.sub .
		            cp -f /usr/share/libtool/config/config.guess .
                else
		            sudo cp -f /usr/share/libtool/config/config.sub .
		            sudo cp -f /usr/share/libtool/config/config.guess .
                fi
            fi
            # Unset CFLAGS for zlib since it won't build otherwise.
            if [ $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE == $ISENSE_THIRDP_PACKAGE_ZLIB ]
            then
                exportAndPrintOutput ISENSE_THIRDP_TEMP_CFLAGS=$CFLAGS;
                unset CFLAGS;
            fi
            if [ $? -eq 0 ]
            then
                make distclean;
                if [ $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE == $ISENSE_THIRDP_PACKAGE_GTK ]
                then
                    # libtoolize --force --copy
                    # aclocal
                    # autoheader
                    # autoconf
                    # automake -a
                    echo ""
                fi
                echo "---------------------------------------------------------------"
                echo "CFLAGS: " $CFLAGS
                echo "LDFLAGS: " $LDFLAGS
                echo "CONFIGURE: ./configure " $ISENSE_THIRDP_CONFIG_AND_BUILD_CONFIG;
                echo "---------------------------------------------------------------"
                ./configure $ISENSE_THIRDP_CONFIG_AND_BUILD_CONFIG;
                if [ $? -eq 0 ]
                then
                    make uninstall;
                    make clean;
                    make;

                    if [ $? -eq 0 ]
                    then
                        make install;
                        if [ $? -eq 0 ]
                        then
                            echo "ISENSE WEBKIT CROSS COMPILE"
                            echo "==========================="
                            echo "Package Build Success";
                            # Restore CFLAGS env variable as we've unset while compiling zlib
                            if [ $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE == $ISENSE_THIRDP_PACKAGE_ZLIB ]
                            then
                                echo "ISENSE WEBKIT CROSS COMPILE"
                                echo "==========================="
                                echo "Restoring the CFLAGS environment variable for others to use..."
                                exportAndPrintOutput CFLAGS=$ISENSE_THIRDP_TEMP_CFLAGS
                                echo "CFLAGS restored to $CFLAGS"
                            fi
                            return 1;
                        else
                            echo "Error Make Install for $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE";
                        fi
                    else
                        echo "Error Make $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE";
                    fi
                else
                    echo "Error Configure $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE";
                fi
            else
                echo "Error changing directory $ISENSE_THIRDP_CONFIG_AND_BUILD_DIR";
            fi
        else
            echo "Error extracting package $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE";
        fi
    else
        echo "Error changing to packages directory $ISENSE_THIRDP_PACKAGES_PATH";
    fi

    echo "Building  $ISENSE_THIRDP_CONFIG_AND_BUILD_PACKAGE failed!";
    echo "ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR = " $ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR;
    exportAndPrintOutput LD_LIBRARY_PATH=$ISENSE_THIRDP_ORIG_LD_LIBRARY_PATH
    return 0;
}

#GLIB Cache Varible Macros
exportAndPrintOutput glib_cv_stack_grows=no
exportAndPrintOutput glib_cv_uscore=no
exportAndPrintOutput glib_cv_monotonic_clock=no
exportAndPrintOutput ac_cv_func_posix_getpwuid_r=yes
exportAndPrintOutput ac_cv_func_posix_getgrgid_r=yes

ISENSE_CONFIG_AND_BUILD_ARRAY=\
( $ISENSE_THIRDP_PACKAGE_JPEG $ISENSE_THIRDP_DIR_JPEG "$ISENSE_THIRDP_BUILD_JPEG_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_ICONV $ISENSE_THIRDP_DIR_ICONV "$ISENSE_THIRDP_BUILD_ICONV_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_TIFF $ISENSE_THIRDP_DIR_TIFF "$ISENSE_THIRDP_BUILD_TIFF_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_ZLIB $ISENSE_THIRDP_DIR_ZLIB "$ISENSE_THIRDP_BUILD_ZLIB_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_PNG $ISENSE_THIRDP_DIR_PNG "$ISENSE_THIRDP_BUILD_PNG_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_GLIB $ISENSE_THIRDP_DIR_GLIB "$ISENSE_THIRDP_BUILD_GLIB_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_XML2 $ISENSE_THIRDP_DIR_XML2 "$ISENSE_THIRDP_BUILD_XML_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_ATK $ISENSE_THIRDP_DIR_ATK "$ISENSE_THIRDP_BUILD_ATK_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_FREETYPE $ISENSE_THIRDP_DIR_FREETYPE "$ISENSE_THIRDP_BUILD_FREE_TYPE_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_EXPAT $ISENSE_THIRDP_DIR_EXPAT "$ISENSE_THIRDP_BUILD_EXPAT_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_FONTCONFIG $ISENSE_THIRDP_DIR_FONTCONFIG "$ISENSE_THIRDP_BUILD_FONTCONFIG_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_PIXMAN $ISENSE_THIRDP_DIR_PIXMAN "$ISENSE_THIRDP_BUILD_PIXMAN_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_CAIRO $ISENSE_THIRDP_DIR_CAIRO "$ISENSE_THIRDP_BUILD_CAIRO_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_POPT $ISENSE_THIRDP_DIR_POPT "$ISENSE_THIRDP_BUILD_POPT_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_PANGO $ISENSE_THIRDP_DIR_PANGO "$ISENSE_THIRDP_BUILD_PANGO_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_GTK $ISENSE_THIRDP_DIR_GTK "$ISENSE_THIRDP_BUILD_GTK_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_GPERF $ISENSE_THIRDP_DIR_GPERF "$ISENSE_THIRDP_BUILD_GPERF_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_LIBGPGERROR $ISENSE_THIRDP_DIR_LIBGPGERROR "$ISENSE_THIRDP_BUILD_LIBGPGERROR_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_LIBGCRYPT $ISENSE_THIRDP_DIR_LIBGCRYPT "$ISENSE_THIRDP_BUILD_LIBGCRYPT_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_GNUTLS $ISENSE_THIRDP_DIR_GNUTLS "$ISENSE_THIRDP_BUILD_GNUTLS_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_SQLITE $ISENSE_THIRDP_DIR_SQLITE "$ISENSE_THIRDP_BUILD_SQLITE_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_LIBSOUP $ISENSE_THIRDP_DIR_LIBSOUP "$ISENSE_THIRDP_BUILD_LIBSOUP_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_LIBUNGIF $ISENSE_THIRDP_DIR_LIBUNGIF "$ISENSE_THIRDP_BUILD_LIBUNGIF_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_ENCHANT $ISENSE_THIRDP_DIR_ENCHANT "$ISENSE_THIRDP_BUILD_ENCHANT_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_LIBXSLT $ISENSE_THIRDP_DIR_LIBXSLT "$ISENSE_THIRDP_BUILD_LIBXSLT_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_ICU $ISENSE_THIRDP_DIR_ICU "$ISENSE_THIRDP_BUILD_ICU_CONFIG"\
 $ISENSE_THIRDP_PACKAGE_WEBKIT $ISENSE_THIRDP_DIR_WEBKIT "$ISENSE_THIRDP_BUILD_WEBKIT_CONFIG" )

ISENSE_CONFIG_AND_BUILD_ARRAY_LENGTH=${#ISENSE_CONFIG_AND_BUILD_ARRAY[@]}
ISENSE_CONFIG_AND_BUILD_VAR=0
for ((  ISENSE_CONFIG_AND_BUILD_VAR = 0 ;  ISENSE_CONFIG_AND_BUILD_VAR < $ISENSE_CONFIG_AND_BUILD_ARRAY_LENGTH;  ISENSE_CONFIG_AND_BUILD_VAR+=3  ))
do
    #Continue building the packages from whatever is left
    if [ $ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR -ge 1 ]
    then
        ISENSE_CONFIG_AND_BUILD_VAR=`expr \( 3 \* $ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR \)`
    fi

    # ICU specific operations
    if [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_ICU" ]
    then
        # First extract and build ICU package for host
        unalias cp
        exportAndPrintOutput ISENSE_THIRDP_TEMP_LDFLAGS=$LDFLAGS
        exportAndPrintOutput ISENSE_THIRDP_TEMP_LD_LIBRARY_PATH=$LD_LIBRARY_PATH
        cd $ISENSE_THIRDP_PACKAGES_PATH
        if [ "$USER" == "root" ]
        then
            cp -fr $ISENSE_THIRDP_PACKAGE_ICU $ISENSE_THIRDP_TMP_BUILD_PATH
        else
            sudo cp -fr $ISENSE_THIRDP_PACKAGE_ICU $ISENSE_THIRDP_TMP_BUILD_PATH
        fi
        cd $ISENSE_THIRDP_TMP_BUILD_PATH
        rm -fr icu
        tar -xf $ISENSE_THIRDP_PACKAGE_ICU
        cd icu/source
        echo $ISENSE_THIRDP_BUILD_ICU_CONFIG
        unset CC CXX AR RANLIB LD NM STRIP CXXFLAGS CPPFLAGS CFLAGS LDFLAGS LD_LIBRARY_PATH
        ./configure $ISENSE_THIRDP_BUILD_HOST_ICU_CONFIG
        make clean
        make 
        if [ $? -ne 0 ]
        then
            echo "Building failed :("
            exportAndPrintOutput LD_LIBRARY_PATH=$ISENSE_THIRDP_ORIG_LD_LIBRARY_PATH
            break;
        fi
        cd $ISENSE_THIRDP_PACKAGES_PATH;
        echo "ISENSE WEBKIT CROSS COMPILE"
        echo "==========================="
        echo "Package ${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR+1]} built successfully for host"
        exportAndPrintOutput CC=$ISENSE_THIRDP_CC
        exportAndPrintOutput CXX=$ISENSE_THIRDP_CXX
        exportAndPrintOutput AR=$ISENSE_THIRDP_AR
        exportAndPrintOutput RANLIB=$ISENSE_THIRDP_RANLIB
        exportAndPrintOutput LD=$ISENSE_THIRDP_LD
        exportAndPrintOutput NM=$ISENSE_THIRDP_NM
        exportAndPrintOutput STRIP=$ISENSE_THIRDP_STRIP
        exportAndPrintOutput CXXFLAGS=$ISENSE_THIRDP_CXXFLAGS
        exportAndPrintOutput CPPFLAGS=$ISENSE_THIRDP_CPPFLAGS
        exportAndPrintOutput CFLAGS=$ISENSE_THIRDP_CFLAGS
        exportAndPrintOutput LDFLAGS=$ISENSE_THIRDP_TEMP_LDFLAGS
        exportAndPrintOutput LD_LIBRARY_PATH=$ISENSE_THIRDP_TEMP_LD_LIBRARY_PATH
        # Work around for this bug: "Bug 326021 - dev-libs/icu-4.4.1 won't compile when using a large CFLAGS string"
        exportAndPrintOutput ISENSE_THIRDP_TEMP_CXXFLAGS=$CXXFLAGS
        exportAndPrintOutput ISENSE_THIRDP_TEMP_CFLAGS=$CFLAGS
        exportAndPrintOutput ISENSE_THIRDP_TEMP_CPPFLAGS=$CPPFLAGS
        exportAndPrintOutput CXXFLAGS="-I$ISENSE_THIRDP_INSTALL_PATH/include -I$ISENSE_THIRDP_INSTALL_PATH/kernel/include -g -O2"
        exportAndPrintOutput CPPFLAGS=$CXXFLAGS
        exportAndPrintOutput CFLAGS=$CXXFLAGS
    fi

    # ATK specific operations
    if [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_ATK" ] || [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_GNUTLS" ]
    then
        exportAndPrintOutput ISENSE_THIRDP_TEMP_LDFLAGS=$LDFLAGS
  #      LDFLAGS="-L$ISENSE_THIRDP_INSTALL_PATH/lib -liconv "
        LDFLAGS="$LDFLAGS -liconv"
    fi
  
    # LIBGCRYPT specific operations
    if [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_LIBGCRYPT" ]
    then
       ln -s $ISENSE_THIRDP_BUILD_SDK_PATH /home/clfs 
       cp $ISENSE_THIRDP_BUILD_SDK_PATH/$ISENSE_THIRDP_TARGET_ARCH/lib/libstdc++.la $ISENSE_THIRDP_BUILD_SDK_PATH/lib/
       exportAndPrintOutput ISENSE_THIRDP_TEMP_LDFLAGS=$LDFLAGS
       LDFLAGS="$LDFLAGS $ISENSE_THIRDP_BUILD_SDK_PATH/lib/libstdc++.so "
    fi

    if [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_PANGO" ]
    then
       exportAndPrintOutput ISENSE_THIRDP_TEMP_LDFLAGS=$LDFLAGS
       LDFLAGS="-L$ISENSE_THIRDP_INSTALL_PATH/lib"
    fi

    # FontConfig specific operations
    if [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_FONTCONFIG" ]
    then
        exportAndPrintOutput ISENSE_THIRDP_TEMP_CXXFLAGS=$CXXFLAGS
        exportAndPrintOutput ISENSE_THIRDP_TEMP_CFLAGS=$CFLAGS
        exportAndPrintOutput ISENSE_THIRDP_TEMP_CPPFLAGS=$CPPFLAGS
        exportAndPrintOutput ISENSE_THIRDP_TEMP_LDFLAGS=$LDFLAGS
        LDFLAGS="-L$ISENSE_THIRDP_INSTALL_PATH/lib"
        exportAndPrintOutput CXXFLAGS="-I$ISENSE_THIRDP_INSTALL_PATH/include -I$ISENSE_THIRDP_INSTALL_PATH/kernel/include -g -O2"
        exportAndPrintOutput CPPFLAGS=$CXXFLAGS
        exportAndPrintOutput CFLAGS=$CXXFLAGS
    fi

    # GTK specific operations
    if [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_GTK" ]
    then
        exportAndPrintOutput ISENSE_THIRDP_TEMP_LDFLAGS=$LDFLAGS
        LDFLAGS="-L$ISENSE_THIRDP_SYSTEM/iSense/lib -L$ISENSE_THIRDP_INSTALL_PATH/lib -L$ISENSE_THIRDP_CROSS_ROOTFS_PATH/lib -lfontconfig -ltiff -ljpeg -lfreetype -lxml2 -lfreetype -lfontconfig -lpng -lm -lpangoft2-1.0 -lpango-1.0 -lpixman-1 -lglib-2.0 -liconv -latk-1.0 -lpangocairo-1.0 -lcairo -lgobject-2.0 -lgmodule-2.0 -lstdc++ $ISENSE_THIRDP_LIBRARIES"
    fi

    echo "ISENSE WEBKIT CROSS COMPILE"
    echo "==========================="
    echo "isense_config_and_build parameters"
    echo "ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR] ${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}"
    echo "ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR+1] ${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR+1]}"
    echo "ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR+2] ${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR+2]}"

    # WebKit specific operations
    if [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" != "$ISENSE_THIRDP_PACKAGE_WEBKIT" ]
    then
        isense_config_and_build ${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]} ${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR+1]} "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR+2]}"
        exportAndPrintOutput ISENSE_THIRDP_CONFIG_AND_BUILD_RETVAL=$?
    else
        exportAndPrintOutput icu_config="$ISENSE_THIRDP_INSTALL_PATH/bin/icu-config"
        exportAndPrintOutput CFLAGS="$CXXFLAGS -std=gnu99 -O0 -g "
        exportAndPrintOutput CPPFLAGS="$CXXFLAGS -O0 -g "
        cd ${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR+1]}
        ISENSE_THIRDP_CONFIG_AND_BUILD_RETVAL=0
        cd WebKitBuild/Release
        make clean;
        make distclean;
        cd ../../
        libtoolize --force --copy
        aclocal
        autoheader
        autoconf
        automake -a
        $ISENSE_THIRDP_BUILD_WEBKIT_CONFIG
        if [ $? -eq 0 ]
        then
            cd WebKitBuild/Release
            make install
            if [ $? -eq 0 ]
            then
                ISENSE_THIRDP_CONFIG_AND_BUILD_RETVAL=1
                cp -f Programs/GtkLauncher $ISENSE_THIRDP_INSTALL_PATH/bin
            fi
        else
            echo "---------------------------------------------------------------"
            echo "ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR = " $ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR;
            echo "CFLAGS: " $CFLAGS
            echo "LDFLAGS: " $LDFLAGS
            echo "CONFIGURE: " $ISENSE_THIRDP_BUILD_WEBKIT_CONFIG;
            echo "PATH: " $PATH;
            echo "---------------------------------------------------------------"
        fi
    fi

    if [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_GTK" ] 
    then
        echo "ISENSE WEBKIT CROSS COMPILE"
        echo "==========================="
        echo "Restoring the LDFLAGS environment variable for others to use..."
        exportAndPrintOutput LDFLAGS=$ISENSE_THIRDP_TEMP_LDFLAGS
        echo "LDFLAGS restored to $LDFLAGS"
    fi

    if [ [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_ATK" ] || [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_GNUTLS" ] ] 
    then
        echo "ISENSE WEBKIT CROSS COMPILE"
        echo "==========================="
        echo "Restoring the LDFLAGS environment variable for others to use..."
        exportAndPrintOutput LDFLAGS=$ISENSE_THIRDP_TEMP_LDFLAGS
        echo "LDFLAGS restored to $LDFLAGS"
    fi

    if [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_LIBGCRYPT" ]
    then
        echo "ISENSE WEBKIT CROSS COMPILE"
        echo "==========================="
        echo "Restoring the LDFLAGS environment variable for others to use..."
        exportAndPrintOutput LDFLAGS=$ISENSE_THIRDP_TEMP_LDFLAGS
        echo "LDFLAGS restored to $LDFLAGS"
    fi

    if [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_PANGO" ]
    then
        echo "ISENSE WEBKIT CROSS COMPILE"
        echo "==========================="
        echo "Restoring the LDFLAGS environment variable for others to use..."
        exportAndPrintOutput LDFLAGS=$ISENSE_THIRDP_TEMP_LDFLAGS
        echo "LDFLAGS restored to $LDFLAGS"
    fi



    if [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_FONTCONFIG" ] || [ "${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR]}" == "$ISENSE_THIRDP_PACKAGE_ICU" ]
    then
        echo "ISENSE WEBKIT CROSS COMPILE"
        echo "==========================="
        echo "Restoring the CXXFLAGS, CFLAGS, CXXFLAGS environment variables for others to use..."
        exportAndPrintOutput CXXFLAGS=$ISENSE_THIRDP_TEMP_CXXFLAGS
        exportAndPrintOutput CFLAGS=$ISENSE_THIRDP_TEMP_CFLAGS
        exportAndPrintOutput CPPFLAGS=$ISENSE_THIRDP_TEMP_CPPFLAGS
        exportAndPrintOutput LDFLAGS=$ISENSE_THIRDP_TEMP_LDFLAGS
        echo "CXXFLAGS restored to $CXXFLAGS"
        echo "CFLAGS restored to $CFLAGS"
        echo "CPPFLAGS restored to $CPPFLAGS"
    fi

    if [ $ISENSE_THIRDP_CONFIG_AND_BUILD_RETVAL -eq 0 ]
    then
        echo "isense_config_and_build failed in package ${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR+1]} :("
        exportAndPrintOutput LD_LIBRARY_PATH=$ISENSE_THIRDP_ORIG_LD_LIBRARY_PATH
        break;
    else
        echo "ISENSE WEBKIT CROSS COMPILE"
        echo "==========================="
        echo "Package ${ISENSE_CONFIG_AND_BUILD_ARRAY[$ISENSE_CONFIG_AND_BUILD_VAR+1]} built successfully"
        exportAndPrintOutput ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR=`expr $ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR + 1`
        echo "ISENSE WEBKIT CROSS COMPILE"
        echo "==========================="
        echo "Packages built so far = $ISENSE_THIRDP_PACKAGES_BUILT_SO_FAR"
    fi

done

if [ $ISENSE_CONFIG_AND_BUILD_VAR -ge $ISENSE_CONFIG_AND_BUILD_ARRAY_LENGTH ]
then
    echo ""
    echo "-------------------------------------------------------"
    echo "ISENSE WEBKIT CROSS COMPILE"
    echo "==========================="
    echo "Congratulations! All Packages Built Successfully!"

#Calculate build time
    ISENSE_THIRDP_END_TIME=`date +%s`;
    ISENSE_THIRDP_TIME_TAKEN=`expr $ISENSE_THIRDP_END_TIME - $ISENSE_THIRDP_START_TIME`;
    ISENSE_THIRDP_BUILD_TIME=$(formatBuildTime `expr $ISENSE_THIRDP_END_TIME - $ISENSE_THIRDP_START_TIME`);
    echo "Time taken to build all packages: $ISENSE_THIRDP_BUILD_TIME"
    echo "-------------------------------------------------------"
    echo ""
    echo "Copying Library to DTV Platform service path"
  
    cp -Rf $ISENSE_THIRDP_INSTALL_PATH/bin/GtkLauncher $ISENSE_THIRDP_BUILD_ROOT/../project_build_i686/IntelCE/root/iSense/bin/
#    cp  -RF/$ISENSE_THIRDP_INSTALL_PATH/lib/ -name "*.so*" -exec rm -rf {}\;
#
#   cd $ISENSE_PLATFORM_SOURCE/Service/source/html/CE4200/webkit_lib/
#	rm -rf *
    cp -Rf $ISENSE_THIRDP_INSTALL_PATH/lib/* $ISENSE_PLATFORM_SOURCE/Service/source/html/CE4200/webkit_lib/
    cd $ISENSE_PLATFORM_SOURCE/Service/source/html/CE4200/webkit_lib/
    rm -rvf *.la
    cd -
    cp $ISENSE_THIRDP_DIR_WEBKIT/WebKitBuild/Release/Programs/GtkLauncher $ISENSE_THIRDP_BUILD_ROOT/../project_build_i686/IntelCE/root/iSense/bin/

#Restore original path
    exportAndPrintOutput PATH=$ISENSE_THIRDP_TEMPPATH
    unset `env | grep ISENSE | awk -F= '{print $1}'`
    unset CC CXX AR RANLIB LD NM STRIP CXXFLAGS CPPFLAGS CFLAGS
    exportAndPrintOutput LD_LIBRARY_PATH=$ISENSE_THIRDP_ORIG_LD_LIBRARY_PATH
fi

