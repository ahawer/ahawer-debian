#!/bin/sh

curl wttr.in/Rødby?format=j1 | sed 40q > ~/.config/weather.txt

