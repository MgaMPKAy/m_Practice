#!/bin/bash

U_ARCHIVES_DIR=$KFAT1/bin
MISC_ARCHIVES_DIR=~/misc/bin
TMP_ROOT=/tmp/tmproot
TMP_BIN_PATH=$TMP_ROOT/bin
SETUPED_FILE=$TMP_ROOT/setuped

## Handle args
if [ -z "$1" ]; then
    echo "Usage: a-setup target"
    exit
fi

## Special setups
case "$1" in
    "list")
	if [ -e $U_ARCHIVES_DIR ]; then
	    echo "U:"
	    ls $U_ARCHIVES_DIR
	fi
	echo "MISC:"
	ls $MISC_ARCHIVES_DIR
	exit
	;;
    "kfat1")
	a-mount-kfat1
	exit
	;;
    "devfs")
	a-mount-devfs
	exit
	;;
esac

TARGET=$1

## Check if setuped
if [ -e $SETUPED_FILE ]; then
    SETUPED=$(grep -i $TARGET $SETUPED_FILE)
else
    SETUPED=""
fi
if [ -n "$SETUPED" ]; then
    echo "$SETUPED already setuped"
    exit
fi

## Set up source
# Try U_ARCHIVES_DIR
if [ -e $U_ARCHIVES_DIR ]; then
    ARCHIVE_FILE=$(ls $U_ARCHIVES_DIR | grep -i $TARGET)
    ARCHIVES_DIR=$U_ARCHIVES_DIR
fi

# Try ARCHIVES_DIR
if [ -z "$ARCHIVE_FILE" ]; then
    ARCHIVE_FILE=$(ls $MISC_ARCHIVES_DIR | grep -i $TARGET)
    ARCHIVES_DIR=$MISC_ARCHIVES_DIR
fi

if [ -z "$ARCHIVE_FILE" ]; then
    echo "Can not found $TARGET"
    exit
fi

## Set up target
CURRENT_DIR=$(pwd)
cd $TMP_ROOT
echo copy from $ARCHIVES_DIR/$ARCHIVE_FILE
tar xf $ARCHIVES_DIR/$ARCHIVE_FILE && echo $ARCHIVE_FILE >> $SETUPED_FILE
cd $CURRENT_DIR
