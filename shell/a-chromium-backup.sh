#!/bin/bash

CONFIG_DIR=/tmp
ARCHIVE_FILE=/home/adlezz/setup/chromium.tar.gz
ARCHIVE_FILENAME=chromium.tar.gz

if [ -d $CONFIG_DIR/chromium ]; then
    cd $CONFIG_DIR
    tar acf $ARCHIVE_FILENAME chromium
    cp $ARCHIVE_FILENAME $ARCHIVE_FILE
    exit
fi