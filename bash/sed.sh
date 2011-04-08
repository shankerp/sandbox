available_thirdp_path="Thirdp/CE4100"
desired_thirdp_path="Thirdp/CE4200"
isense_system="/media/work/Dropbox/workspace/sandbox/scripts/system"

sed -i "s|prefix=[a-zA-Z0-9_'/\]*$available_thirdp_path|prefix=$isense_system/$desired_thirdp_path|g" pango-arabic-fc.la
sed -i "s|-L[a-zA-Z0-9_'/\.\-]*$available_thirdp_path|-L$isense_system/$desired_thirdp_path|g" pango-arabic-fc.la
sed -i "s|-I[a-zA-Z0-9_'/\.\-]*$available_thirdp_path|-I$isense_system/$desired_thirdp_path|g" pango-arabic-fc.la
sed -i "s|-L[a-zA-Z0-9_'/\.\-]*build_i686/staging_dir|-L$sdk_path/build_i686/staging_dir|g" pango-arabic-fc.la
sed -i "s|-I[a-zA-Z0-9_'/\.\-]*build_i686/staging_dir|-I$sdk_path/build_i686/staging_dir|g" pango-arabic-fc.la
sed -i "s|-L[a-zA-Z0-9_'/\.\-]*build_i686/i686-linux-elf|-L$sdk_path/build_i686/i686-linux-elf|g" pango-arabic-fc.la
sed -i "s|-I[a-zA-Z0-9_'/\.\-]*build_i686/i686-linux-elf|-I$sdk_path/build_i686/i686-linux-elf|g" pango-arabic-fc.la
sed -i "s|libdir=[a-zA-Z0-9_'/\.\-]*$available_thirdp_path/lib|libdir='$isense_system/$desired_thirdp_path/lib|g" pango-arabic-fc.la
sed -i "s|[a-zA-Z0-9_'/\.\-]*$available_thirdp_path/lib/${file_names[$j]}|$isense_system/$desired_thirdp_path/lib/${file_names[$j]}|g" pango-arabic-fc.la
sed -i "s|[a-zA-Z0-9_'/\.\-]*usr/local/lib/libdirectfb.la|$sdk_path/build_i686/staging_dir/usr/local/lib/libdirectfb.la|g" pango-arabic-fc.la
sed -i "s|[a-zA-Z0-9_'/\.\-]*usr/local/lib/libdirect.la|$sdk_path/build_i686/staging_dir/usr/local/lib/libdirect.la|g" pango-arabic-fc.la
sed -i "s|[a-zA-Z0-9_'/\.\-]*usr/local/lib/libfusion.la|$sdk_path/build_i686/staging_dir/usr/local/lib/libfusion.la|g" pango-arabic-fc.la
sed -i "s|libdir=[a-zA-Z0-9_'/\.\-]*$available_thirdp_path/lib|libdir='$isense_system/$desired_thirdp_path/lib|g" pango-arabic-fc.la
sed -i "s|\/[/]*|\/|g" pango-arabic-fc.la
