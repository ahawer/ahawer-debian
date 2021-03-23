#!/bin/sh

curl wttr.in/Vejleby?format=j1 | sed 40q > ~/.config/weather.txt

