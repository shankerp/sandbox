number="$1"
divisor="$2"
ceil() {
    var=`awk -vnumber="$number" -vdiv="$divisor" '
    function ceil(x){return (x == int(x)) ? x : int(x)+1 }
    BEGIN{ print ceil(number/div) }'`
echo "${var}"
}
varu=$(ceil)
echo "Var is $varu"
