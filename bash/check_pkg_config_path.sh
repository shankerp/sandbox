PARSE="`env | grep PKG_CONFIG_PATH | awk -F= '{print $1}'`x"
if [ $PARSE == "PKG_CONFIG_PATHx" ]
then
echo "PARSE IS PKG_CONFIG_PATH"
else
echo "PARSE IS NOT PKG_CONFIG_PATH"
fi
