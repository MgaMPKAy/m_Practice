#!/bin/bash

USER=username
USERPW=password
APPKEY=12345678

BASEURL=https://api.weibo.com/2 

#curl -u $USER:$USERPW  -d source=$APPKEY -d status="hello" -d lat=0 -d long=0  $BASEURL/statuses/update.json

curl -G -u $USER:$USERPW  -d source=$APPKEY $BASEURL/statuses/public_timeline.json

echo