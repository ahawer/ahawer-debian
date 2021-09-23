#!/bin/sh

aptitude search '~U' | wc -l | sed 40q > ~/.config/upgrades.txt

