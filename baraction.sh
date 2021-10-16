#!/bin/bash
# baraction.sh for spectrwm status bar

## DISK
hdd() {
  hdd="$(df -h | awk ' NR==4  { print  $3,   $5 } ')"
  echo "/   $hdd"
}
hdd1() {
  hdd1="$(df -h | awk ' NR==7  { print  $3,   $5 } ')"
  echo "~   $hdd1"
}
## RAM
mem() {
  mem=`free | awk '/Mem/ {printf "%d Mb / %d Mb\n", $3 / 1024.0, $2 / 1024.0 }'`
  echo "RAM: $mem"
}
## CPU
cpu() {
  read cpu a b c previdle rest < /proc/stat
  prevtotal=$((a+b+c+previdle))
  sleep 0.5
  read cpu a b c idle rest < /proc/stat
  total=$((a+b+c+idle))
  cpu=$((100*( (total-prevtotal) - (idle-previdle) ) / (total-prevtotal) ))
  echo " CPU: $cpu%"
}

## CPU Temp

CPUTEMP() {
  CPUTEMP="$(sensors | grep Tctl | awk '{print $2" "$3" "$4" "$5}' | sed 's/"//g')"
  echo "$CPUTEMP"
}
## MUSIC
#mpd(){
#  song="$(mpc current)"
#  status="$(mpc status | grep paused | awk '{print $2}')"
#  echo -e "$song"
#}
## UPGRADES
upgrades() {
#	upgrades="$(apt list --upgradable | wc -l)"    # "$(aptitude search '~U' | wc -l)"
	upgrades="$(cat ~/.config/upgrades.txt)"
	echo " UPG: $upgrades "
}
## NET SPEED
#rtx() {
#    _interface=$(ip route | grep '^default' | awk '{print $5}')
#
#  for a in $_interface; do
#    _r=$(cat /sys/class/net/$a/statistics/rx_bytes)
#    _t=$(cat /sys/class/net/$a/statistics/tx_bytes)
#    echo $_r    $_t
#  done
#}

netspeed() { 

R1=`cat /sys/class/net/eno1/statistics/rx_bytes`
T1=`cat /sys/class/net/eno1/statistics/tx_bytes`
sleep 1
R2=`cat /sys/class/net/eno1/statistics/rx_bytes`
T2=`cat /sys/class/net/eno1/statistics/tx_bytes`
TBPS=`expr $T2 - $T1`
RBPS=`expr $R2 - $R1`
TKBPS=`expr $TBPS / 1024`
RKBPS=`expr $RBPS / 1024`
#icon="⬇️"
#icon1="⬆️"
printf " %s %s \\n"  "> $RKBPS kb  "  "< $TKBPS kb"



#    [[ -z $Rx1 ]] || [[ -z $Tx1 ]] && return
#
#        Rx2=$(rtx |awk '{sum+=$1} END {print sum}')
#        Tx2=$(rtx |awk '{sum+=$2} END {print sum}')
#        RBps=$((Rx2-Rx1))
#        TBps=$((Tx2-Tx1))
#        Rxps="$((RBps/1024))"
#        Txps="$((TBps/1024))"
#        
#        RM=$((Rxps/1024))
#        Rm=$((Rxps%1024*10/1024))
#        TM=$((Txps/1024))
#        Tm=$((Txps%1024))
#
#        [[ $Rm -ge 100 ]] && Rm=".$(echo $Rm | cut -c1-1)" || Rm=""
#        [[ $Tm -ge 100 ]] && Tm=".$(echo $Tm | cut -c1-1)" || Tm=""

#        [[ -n $(ip route | grep '^default' | awk '{print $5}') ]] &&
#        if [[ $RM -ge 1 ]]; then
#          Rxps="$RM$Rm Mb/s"
#          Txps="$TM$Tm Mb/s"
#        else
#          Rxps="$Rxps kb/s"
#          Txps="$Txps kb/s"
#        fi
#        echo -e "> ${Rxps} < ${Txps}"
}
### netspeed
           
       #     Rx1=$(rtx |awk '{sum+=$1} END {print sum}')
       #     Tx1=$(rtx |awk '{sum+=$2} END {print sum}')

# NET
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
##vol() {
#    vol=`amixer get Master | awk -F'[][]' 'END{ print $4":"$2 }' | sed 's/on://g'`
#    echo "VOL: $vol"
#}
vol() {
	vol="$(amixer -D pulse get Master | awk -F'[][]' 'END{ print $4": "$2 }')"
	echo " VOL  $vol "
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

SLEEP_SEC=2

#loops forever outputting a line every SLEEP_SEC secs

# It seems that we are limited to how many characters can be displayed via
# the baraction script output. And the the markup tags count in that limit.
# So I would love to add more functions to this script but it makes the 
# echo output too long to display correctly.
while :; do
#	echo "   |  $(cpu)  |  $(mem)  |  $(hdd)  |  $(network)   $(netspeed)  |  $(weather) $(temp)  |  $(vol)  | "
echo " | +@fg=6; $(cpu)    $(CPUTEMP) +@fg=0; | +@fg=2; $(mem) +@fg=0; | +@fg=3; $(hdd)   $(hdd1) +@fg=0; | +@fg=1; $(network)  $(netspeed) +@fg=0; | +@fg=7; $(upgrades) +@fg=0; | $(weather) $(temp) | +@fg=4; $(vol) +@fg=0; | "
	
## netspeed
           
       #     Rx1=$(rtx |awk '{sum+=$1} END {print sum}')
       #     Tx1=$(rtx |awk '{sum+=$2} END {print sum}')

    	    sleep $SLEEP_SEC
done

