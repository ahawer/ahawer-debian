#!/bin/sh
#xrandr --output HDMI-1 --off --output DP-1 --mode 1920x1080 --pos 1920x0 --rotate normal --output HDMI-2 --primary --mode 1920x1080 --pos 0x0 --rotate normal &
nitrogen --restore &
compton --backend glx --vsync opengl-swc &
lxpolkit &
# pnmixer &
volumeicon &
#pasystray &
blueman-applet &
caffeine-indicator &
pcmanfm &
st -e fish &
claws-mail &
#qutebrowser &
tabbed surf -e &
#trayer --edge top --widthtype request --height 20 &
#xscreensaver -no-splash &
#zoom &
cmst &
dwmblocks &
#exec slstatus &
#start dwm after loop
#while true;  do  /usr/local/bin/dwm > /dev/null; done;
exec dwm
