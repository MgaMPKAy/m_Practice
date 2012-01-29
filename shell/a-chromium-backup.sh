#!/bin/bash

CONFIG_DIR=/tmp
ARCHIVE_FILE=$SETUP_DIR/chromium.tar.gz
ARCHIVE_FILENAME=chromium.tar.gz

# Backup if setuped
if [ ! -d $CONFIG_DIR/chromium ]; then
    echo "Chromium config is not setuped"
else
    cd $CONFIG_DIR
    tar acf $ARCHIVE_FILENAME chromium
    cp $ARCHIVE_FILENAME $ARCHIVE_FILE
    echo "Chromium config is backuped"
fi
