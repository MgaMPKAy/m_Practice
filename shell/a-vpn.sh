#!/bin/bash

CMD=$1

function printHelpMsg()
{
	echo "usage: a-vpn cmd [vender] [address ][username] [password]"
	echo "cmd: up down help"
	echo "vender: vpncup fast tenacy"
	echo "        fast and tenacy reauire address and password"
}

case $CMD in
    "down" )
	sudo killall pptp
	exit
	;;
    "up" )
	VENDER=$2
	case $VENDER in
	    "vpncup" )
		$ADDR=$3
		$PW=password
		$USER=username
		sudo pppd pty  "pptp $ADDR --nolaunchpppd --loglevel 0" \
		    file /etc/ppp/options.pptp user $USER  password $PW \
		    require-mppe require-mschap-v2 noauth nolog
		exit
		;;
	    "fast" )
		ADDR=$3
		PW=$4
		sudo pppd pty  "pptp $ADDR --nolaunchpppd --loglevel 0" \
		    file /etc/ppp/options.pptp user tenacy password $PW \
		    require-mschap-v2 noauth nolog
		exit
		;;
	    "tenacy" )
		ADDR=$3
		PW=$4
		sudo pppd pty "pptp $ADDR --nolaunchpppd --loglevel 0" \
		    file /etc/ppp/options.pptp user tenacy password $PW \
		    require-mppe require-mschap-v2 noauth nolog
		exit
		;;
	    *)
		echo "	vender: vpncup fast tenacy"
		;;
	esac
	;;
    "help" )
	printHelpMsg
	;;
esac
