#!/bin/bash

# $1 -> address
# $2 -> password
# need /etc/ppp/ip-up.local and /etc/ppp/ip-down.local
# killall pppd/pptp to disconnect
sudo pppd pty "pptp $1 --nolaunchpppd --loglevel 0" \
file /etc/ppp/options.pptp user tenacy password $2 
require-mppe require-mschap-v2 noauth nolog
