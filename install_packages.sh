#!/bin/bash

sudo apt update && sudo apt install xorg xserver-xorg build-essential xutils mesa-utils xinit firmware-linux firmware-linux-nonfree materia-gtk-theme git wget fish synaptic lightdm lightdm-gtk-greeter lightdm-gtk-greeter-settings awesome lxappearance nitrogen arandr kitty compton pcmanfm volumeicon-alsa backintime-qt4 lm-sensors caffeine-indicator mpv pavucontrol fonts-font-awesome fonts-fork-awesome fonts-powerline scrot vlc firefox-esr qutebrowser geary lxpolkit synapse grsync gufw recoll spectrwm vim geany vifm feh qpdfview -yy

sudo systemctl enable lightdm
