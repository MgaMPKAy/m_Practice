#!/bin/bash

CONFIG_DIR=/tmp
ARCHIVE_FILE=/home/adlezz/setup/chromium.tar.gz

if [ -d $CONFIG_DIR/chromium ]; then
    echo a-chromium-startuo: Already set up
    exit 0
fi

cd $CONFIG_DIR
tar xf $ARCHIVE_FILE
exit 0
