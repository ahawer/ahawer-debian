#!/bin/sh

sudo aptitude search '~U' | wc -l | sed 40q > ~/.config/upgrades.txt

