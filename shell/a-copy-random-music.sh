#!/bin/bash

# how many file to copy
COUNT=$1

# copy from
FROM=$KFAT1/Sounds/Music

# copy to
TARGET=Music

# ensure at least one arg is given
if [ -z $1 ] ; then
    echo 'usage: a-copy-random-music [num|all]'
    exit
fi

# set up target dir
if [ -f $TARGET ]; then
    echo "error: target is not dir"
    exit
elif [ ! -d $TARGET ]; then
    mkdir $TARGET
fi

# copy
if [ $COUNT == 'inplace' ]; then
    find  $FROM -name "*.mp3" > playlist
elif [ $COUNT == "all" ]; then
    find $FROM -name "*.mp3" -print0 \
	| xargs -0 -r --verbose -I file cp file $TARGET
else
    find $KFAT1/Sounds/Music/ -name "*.mp3" -exec echo '"{}"' \; \
	| sort -R --random-source=/dev/urandom \
	| head -$COUNT \
	| xargs --verbose -I file cp file ./Music
fi

# build playlist
if [ $COUNT != 'inplace' ]; then
    ls $TARGET/*.mp3 > playlist
fi

# optional: start playing immediately
if [[ "$2" == "play" ]]; then
    mplayer -playlist playlist -shuffle
fi
