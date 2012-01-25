#!/bin/bash

U_ARCHIVES_DIR=/tmp/workspace/KFAT1/bin
MISC_ARCHIVES_DIR=~/misc/bin
TMP_ROOT=/tmp/tmproot
TMP_BIN_PATH=$TMP_ROOT/bin

if [ -z "$1" ]; then
    echo "Usage: a-setup target"
    exit
fi

if [ "$1" == "list" ]; then
    if [ -e $U_ARCHIVES_DIR ]; then
	echo "U:"
	ls $U_ARCHIVES_DIR;
    fi
    echo "MISC:"
    ls $MISC_ARCHIVES_DIR
    exit
fi

# DO NOT WORK FOR COLLECTIONS, lnxp ect.
TARGET=$1

if [ -e $TMP_BIN_PATH ]; then
    SETUPED=$(ls $TMP_BIN_PATH | grep -i $TARGET)
else
    SETUPED=""
fi


if [ -n "$SETUPED" ]; then
    echo "$TARGET already setuped"
    exit
fi

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

CURRENT_DIR=$(pwd)
cd $TMP_ROOT
echo copy from $ARCHIVES_DIR/$ARCHIVE_FILE
tar xf $ARCHIVES_DIR/$ARCHIVE_FILE
cd $CURRENT_DIR
