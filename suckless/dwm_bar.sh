#!/bin/bash
# bar for DWM status bar
dte(){
        dte="$(date +"%A %d. %B,  %R")"
        echo "$dte"
}

## DISK
hdd() {
 ## hdd="$(df -h | awk ' NR==4  { print  $3,   $5 } ')"
  hdd="$(df -h / | grep dev | awk '{print$3, " "  $5}')"
  echo "  $hdd"
}
## RAM
mem() {
  mem=`free | awk '/Mem/ {printf "%d Mb / %d Mb\n", $3 / 1024.0, $2 / 1024.0 }'`
  echo "  $mem"
}
## CPU
cpu() {
  read cpu a b c previdle rest < /proc/stat
  prevtotal=$((a+b+c+previdle))
  sleep 0.5
  read cpu a b c idle rest < /proc/stat
  total=$((a+b+c+idle))
  cpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))
  echo "  $cpu%"
}
## MUSIC
#mpd(){
#  song="$(mpc current)"
#  status="$(mpc status | grep paused | awk '{print $2}')"
#  echo -e "$song"
#}
## UPGRADES
#upgrades() {
#	upgrades="$(apt list --upgradable | wc -l)"    # "$(aptitude search '~U' | wc -l)"
#	echo " UPG: $upgrades "
#}
## NET SPEED
rtx() {
    _interface=$(ip route | grep '^default' | awk '{print $5}')

  for a in $_interface; do
    _r=$(cat /sys/class/net/$a/statistics/rx_bytes)
    _t=$(cat /sys/class/net/$a/statistics/tx_bytes)
    echo $_r    $_t
  done
}

netspeed() {
    [[ -z $Rx1 ]] || [[ -z $Tx1 ]] && return

        Rx2=$(rtx |awk '{sum+=$1} END {print sum}')
        Tx2=$(rtx |awk '{sum+=$2} END {print sum}')
        RBps=$((Rx2-Rx1))
        TBps=$((Tx2-Tx1))
        Rxps="$((RBps/1024))"
        Txps="$((TBps/1024))"
        
        RM=$((Rxps/1024))
        Rm=$((Rxps%1024*10/1024))
        TM=$((Txps/1024))
        Tm=$((Txps%1024))

        [[ $Rm -ge 100 ]] && Rm=".$(echo $Rm | cut -c1-1)" || Rm=""
        [[ $Tm -ge 100 ]] && Tm=".$(echo $Tm | cut -c1-1)" || Tm=""

        [[ -n $(ip route | grep '^default' | awk '{print $5}') ]] &&
        if [[ $RM -ge 1 ]]; then
          Rxps="$RM$Rm Mb/s"
          Txps="$TM$Tm Mb/s"
        else
          Rxps="$Rxps kb/s"
          Txps="$Txps kb/s"
        fi
        echo -e "> ${Rxps} < ${Txps}"
}
## NET
network(){
    read lo int1 int2 <<< `ip link | sed -n 's/^[0-9]: \(.*\):.*$/\1/p'`
	if iwconfig $int1 >/dev/null 2>&1; then
	    wifi=$int1
	    eth0=$int2
	else 
	    wifi=$int2
	    eth0=$int1
	fi
    ip link show $eth0 | grep 'state UP' >/dev/null && int=$eth0 || int=$wifi
    echo -n "$int"
    ping -c1 -s1 8.8.8.8 >/dev/null 2>&1 && echo "Net ON" || echo "Net OFF"
}
## VOLUME
vol() {
    vol=`amixer get Master | awk -F'[][]' 'END{ print $4":"$2 }' | sed 's/on://g'`
    echo " $vol"
}

## WEATHER
weather() {
	wthr="$(sed 24q ~/.config/weather.txt | grep value | awk '{print $2" "$3" "$4" "$5}' | sed 's/"//g')"
	echo "$wthr"
}

## TEMP
temp() {
	tmp="$(grep temp_C ~/.config/weather.txt | awk '{print $2}' | sed 's/"//g' | sed 's/,/ C/g')"
	echo " $tmp"
}

## STATUS
stat() {
	echo "|  $(cpu) |  $(mem) |  $(hdd) |  $(network)  $(netspeed) |  $(weather)$(temp) |  $(vol) |  $(dte)  |"
}

SLEEP_SEC=1

#loops forever outputting a line every SLEEP_SEC secs

# It seems that we are limited to how many characters can be displayed via
# the baraction script output. And the the markup tags count in that limit.
# So I would love to add more functions to this script but it makes the 
# echo output too long to display correctly.
while true; do

	xsetroot -name "$(stat)"

## netspeed
            Rx1=$(rtx |awk '{sum+=$1} END {print sum}')
            Tx1=$(rtx |awk '{sum+=$2} END {print sum}')

    	    sleep $SLEEP_SEC
done

