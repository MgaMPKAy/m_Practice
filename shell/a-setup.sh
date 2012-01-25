#!/bin/bash

OLDPWD=$(pwd)
TMPROOT=/tmp/tmproot
ARCDIR=~/misc/bin
PROGRAM=$1

function setup() {
    BINNAME=$1
    if [ -n "$2" ] ; then
	FILENAME=$2
    fi
	
    AREADY=$(ls $TMPROOT/bin/ | grep $BINNAME)
    if [ -n "$AREADY" ] ; then
	echo "Alread Setup"
	return
    else
	if [ -z "$FILENAME" ]; then
	    FILENAME=$(ls ~/misc/bin/ | grep -i $BINNAME | head -n 1)
	fi
	tar xf $ARCDIR/$FILENAME
    fi
}

cd /tmp/tmproot/

case "$PROGRAM" in
    "mplayer" ) 
	setup "mplayer" 
	;;
    "redis" )
	setup "redis"
	;;
    "nginx" )
	setup "nginx"
	;;
    "ocaml" ) 
	setup "ocaml"
	;;
    "php" )
	setup "php"
	;;
    "racket" )
	setup "racket"
	;;
    
esac

cd $OLDPWD

