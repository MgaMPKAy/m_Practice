#!/bin/bash

cmd=$1
arg=$2

case "$cmd" in
    "get" )
	amixer sget Master
	;;

    "set" )
	amixer sset Master $arg
	;;
    
    "mute" )
	state=`amixer sget Master | awk '{if (NR == 5) print $6}'`

	if [ $state == "[on]" ]; then
	    amixer sset Master mute > /dev/null
	else
	    amixer sset Master unmute > /dev/null
	fi
	;;

    "down" )
	step=6
	now=`amixer sget Master | awk '{if (NR == 5) print $3}'`
	next=$(($now - $step))

	if [ $((now)) == 0 ]; then
	    exit
	elif [ $((next)) -lt 0 ]; then
	    amixer sset Master 0 > /dev/null
	else
	    amixer sset Master $next > /dev/null
	fi
	;;

    "up" )
	step=6
	now=`amixer sget Master | awk '{if (NR == 5) print $3}'`
	next=$(($now + $step))

	if [ $((now)) == 64 ]; then
	    exit
	elif [ $((next)) -gt 64 ]; then
	    amixer sset Master 64 > /dev/null
	else
	    amixer sset Master $next > /dev/null
	fi
	;;

esac