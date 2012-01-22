#!/bin/bash

PREFIX=/tmp/tmproot/

./configure \
--prefix=$PREFIX \
--enable-nls \
--enable-cli

# export TRANSMISSION_HOME=/tmp/tmproot/etc/transmission