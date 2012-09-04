#!/bin/bash

ffmpeg -i $1 -strict experimental -vcodec mpeg4 -s 320x240 -b:v 192k -r 14 -ar 22050 -ab 32k -f mp4 output.mp4
#ffmpeg -i $1 -vcodec mpeg4 -s 320x240 -b:v 192k -r 14 -ar 22050 -ab 32k -f mp4 output.mp4