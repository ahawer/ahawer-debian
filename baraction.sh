#!/bin/bash
# baraction.sh for spectrwm status bar

## DISK
hdd() {
  hdd="$(df -h | awk ' NR==4  { print  $3,   $5 } ')"
  echo "SSD: $hdd"
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
  echo "CPU: $cpu%"
}
## UPGRADES
#upgrades() {
#        upgrades="$(aptitude search '~U' | wc -l)"
#	echo " UPG: $upgrades "
#}

## VOLUME
vol() {
    vol=`amixer get Master | awk -F'[][]' 'END{ print $4":"$2 }' | sed 's/on://g'`
    echo "VOL: $vol"
}
SLEEP_SEC=3

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

SLEEP_SEC=3

loops forever outputting a line every SLEEP_SEC secs

# It seems that we are limited to how many characters can be displayed via
# the baraction script output. And the the markup tags count in that limit.
# So I would love to add more functions to this script but it makes the 
# echo output too long to display correctly.
while :; do
	echo "     $(cpu)  |  $(mem)  |  $(hdd)  |  $(vol)  |  $(weather) $(temp)  |   "

	sleep $SLEEP_SEC
done

