#!/bin/sh
xrandr --output HDMI-1 --off --output DP-1 --mode 1920x1080 --pos 1920x0 --rotate normal --output HDMI-2 --primary --mode 1920x1080 --pos 0x0 --rotate normal &
nitrogen --restore &
compton &
lxpolkit &
# pnmixer &
#volumeicon &
#pasystray &
#caffeine-indicator &
#pcmanfm &
#st &
#geary &
#firefox-esr &
#xscreensaver &
#zoom &
exec slstatus &
#start dwm after loop
#while true;  do  /usr/local/bin/dwm > /dev/null; done;
exec dwm
