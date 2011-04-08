#!/bin/bash

###################################################################
#
# Fixes dependency libs in la files and pkg-config files
#
# Author : Bharathwaaj Srinivasan <bsrinivasan@celestialsys.com>
#
###################################################################

isense_system=$1
sdk_path=$2
available_thirdp_path="Thirdp/CE4100"
desired_thirdp_path="Thirdp/CE4200"

function get_files_of_type_from()
{
    file_type=$1;
    search_path=$2;
    files=( `find $search_path -name \*.$file_type` )
    num_of_files=${#files[@]}
    var=0
    for ((  var = 0 ;  var < $num_of_files;  var+=1  ))
    do
    echo ${files[$var]}
    done
}

function get_pc_files()
{
    get_files_of_type_from pc $isense_system
}

function get_la_files()
{
    get_files_of_type_from la $isense_system
}

function replace_line_with_pattern()
{
    file_name=$1;
    orig_pattern=$2;
    replace_pattern=$3;
    echo "$file_name $orig_pattern $replace_pattern"
    sed -i "
    /$orig_pattern/ c\
    $replace_pattern
    " $file_name
}

function my_ceil() 
{
    number="$1";
    divisor="$2";
    var=`awk -vnumber="$number" -vdiv="$divisor" '
    function my_ceil(x){return (x == int(x)) ? x : int(x)+1 }
    BEGIN{ print my_ceil(number/div) }'`
    echo "${var}"
}

function print_progress_bar()
{
    bar_char_start="[";
    bar_char_end="]";
    bar_char_empty=".";
    bar_char_full="=";
    bracket_chars=2;
    limit=100;

    let "full_limit = ((($1 - $bracket_chars) * $2) / $limit)";
    let "empty_limit = ($1 - $bracket_chars) - ${full_limit}";
    bar_line="${bar_char_start}";

    for ((j=0; j<full_limit; j++)); do
    bar_line="${bar_line}${bar_char_full}";
    done

    for ((j=0; j<empty_limit; j++)); do
    bar_line="${bar_line}${bar_char_empty}";
    done

    bar_line="${bar_line}${bar_char_end}";
    printf "%3d%% %s" $2 ${bar_line};
}

function apply_fix()
{
    files=( `echo $1` );
    num_of_files=${#files[@]}
    progress_bar_width=$(my_ceil ${num_of_files} 2)

    for ((  var = 0 ;  var < $num_of_files;  var+=1  ))
    do
    sed -i "s|prefix=[a-zA-Z0-9_'/\]*$available_thirdp_path|prefix=$isense_system/$desired_thirdp_path|g" ${files[$var]}
    sed -i "s|-L[a-zA-Z0-9_'/\.\-]*$available_thirdp_path|-L$isense_system/$desired_thirdp_path|g" ${files[$var]}
    sed -i "s|-I[a-zA-Z0-9_'/\.\-]*$available_thirdp_path|-I$isense_system/$desired_thirdp_path|g" ${files[$var]}
    sed -i "s|-L[a-zA-Z0-9_'/\.\-]*build_i686/staging_dir|-L$sdk_path/build_i686/staging_dir|g" ${files[$var]}
    sed -i "s|-I[a-zA-Z0-9_'/\.\-]*build_i686/staging_dir|-I$sdk_path/build_i686/staging_dir|g" ${files[$var]}
    sed -i "s|-L[a-zA-Z0-9_'/\.\-]*build_i686/i686-linux-elf|-L$sdk_path/build_i686/i686-linux-elf|g" ${files[$var]}
    sed -i "s|-I[a-zA-Z0-9_'/\.\-]*build_i686/i686-linux-elf|-I$sdk_path/build_i686/i686-linux-elf|g" ${files[$var]}
    relative=`expr ${var} \* 100`; 
    progress=$(my_ceil ${relative} ${num_of_files})
    print_progress_bar ${progress_bar_width} ${progress}
    echo -en "\r"
    done

    print_progress_bar ${progress_bar_width} 100
    echo -en "\r"
    echo ""
}

function apply_la_fix()
{
    files=( `echo $1` );
    file_names=( `echo $2` );
    num_of_files=${#files[@]}
    progress_bar_width=$(my_ceil ${num_of_files} 2)

    for (( i = 0 ; i < $num_of_files; i+=1 ))
    do
        for (( j = 0 ; j < $num_of_files; j+=1 ))
        do
        sed -i "s|[a-zA-Z0-9_'/\.\-]*$available_thirdp_path/lib/${file_names[$j]}|$isense_system/$desired_thirdp_path/lib/${file_names[$j]}|g" ${files[$i]}
        done
        sed -i "s|[a-zA-Z0-9_'/\.\-]*usr/local/lib/libdirectfb.la|$sdk_path/build_i686/staging_dir/usr/local/lib/libdirectfb.la|g" ${files[$i]}
        sed -i "s|[a-zA-Z0-9_'/\.\-]*usr/local/lib/libdirect.la|$sdk_path/build_i686/staging_dir/usr/local/lib/libdirect.la|g" ${files[$i]}
        sed -i "s|[a-zA-Z0-9_'/\.\-]*usr/local/lib/libfusion.la|$sdk_path/build_i686/staging_dir/usr/local/lib/libfusion.la|g" ${files[$i]}
        sed -i "s|libdir=[a-zA-Z0-9_'/\.\-]*$available_thirdp_path/lib|libdir='$isense_system/$desired_thirdp_path/lib|g" ${files[$i]}
        sed -i "s|\/[/]*|\/|g" ${files[$i]}
        relative=`expr ${i} \* 100`; 
        progress=$(my_ceil ${relative} ${num_of_files})
        print_progress_bar ${progress_bar_width} ${progress}
        echo -en "\r"
    done
    print_progress_bar ${progress_bar_width} 100
    echo -en "\r"
    echo ""
}

function check_trailing_backslash()
{
    length=`echo $isense_system | wc -c`;
    length=`expr ${length} - 1`; 
    c=`echo $isense_system | cut -c $length`;
    if [ $c != '/' ]; then
    isense_system="$isense_system/"
    fi

    length=`echo $sdk_path | wc -c`;
    length=`expr ${length} - 1`; 
    c=`echo $sdk_path | cut -c $length`;
    if [ $c != '/' ]; then
    sdk_path="$sdk_path/"
    fi
}

function main()
{
    pc_files=( $(get_pc_files) );
    num_pc_files=${#pc_files[@]}
    argument=`echo ${pc_files[@]}`
    echo "Applying fix for pkg-config files"
    apply_fix "$argument"

    la_files=( $(get_la_files) );
    num_la_files=${#la_files[@]}

    for (( var = 0 ; var < $num_la_files; var+=1 ))
    do
    la_file_names[$var]=`echo ${la_files[$var]} | awk -F/ '{print $NF}'`;
    done

    argument=`echo ${la_files[@]}`
    argument2=`echo ${la_file_names[@]}`
    echo "Applying first round of fix for la files"
    apply_fix "$argument"
    echo "Applying second round of fix for la files"
    apply_la_fix "$argument" "$argument2"
}

if [ $# != 2 ]; then
echo "Blah!"
echo "Enter isense_system path:"
read isense_system
echo "Enter sdk_path:"
read sdk_path
echo ""
fi
check_trailing_backslash
echo ""
echo "Following are the paths where dependency la files will be updated:"
echo "isense_system --> $isense_system"
echo "sdk_path --> $sdk_path"
echo ""
main
