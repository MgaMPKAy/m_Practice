#!/bin/bash

touchpad="FSPPS/2 Sentelic FingerSensingPad"
state=`xinput list-props "$touchpad" | grep "Device Enabled" | awk '{print $4}'`

enable=1
if [ "$state" = "1" ]; then
    enable=0;
fi

xinput set-prop "$touchpad" "Device Enabled" $enable;