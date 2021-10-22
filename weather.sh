#!/bin/bash

curl wttr.in/Vejleby?format=j1 | sed 40q > ~/.config/weather.txt
curl wttr.in/Vejleby?format=%t | sed 2q > ~/.config/weather_temp.txt

