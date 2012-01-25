#!/bin/bash

PREFIX=/tmp/tmproot

./configure \
--prefix=$PREFIX \
--interp-prefix=$PREFIX/gnemul/qemu-%M \
--target-list="i386-softmmu x86_64-softmmu" \
--disable-kvm \
--python=/usr/bin/python2
