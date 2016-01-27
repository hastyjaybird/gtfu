curl www.sunrisesunset.com >/tmp/whatever
HOUR=`cat /tmp/whatever | grep "San Francisco" | cut -d: -f 3`
MIN=`cat /tmp/whatever | grep "San Francisco" | cut -d: -f 4 | cut -da -f 1`
echo Sunrise will be at: $HOUR:$MIN
WAITH=$(($HOUR-1))
echo Sleeping for "$WAITH"hours and "$MIN". ZZZ
sleep "$WAITH"h "$MIN"m
stty /dev/ttyATH0 300
echo r > /dev/ttyATH0
