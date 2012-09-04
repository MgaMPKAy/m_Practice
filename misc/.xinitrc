#!/bin/sh
#
# ~/.xinitrc
#
# Executed by startx (run your window manager from here)

if [ -d /etc/X11/xinit/xinitrc.d ]; then
  for f in /etc/X11/xinit/xinitrc.d/*; do
    [ -x "$f" ] && . "$f"
  done
  unset f
fi

#xsri --set ~/Pictures/Erio.jpg --center-x
# exec gnome-session
# exec startkde
# exec startxfce4
# ...or the Window Manager of your choicees

xsetroot -cursor_name left_ptr
xmodmap ~/.Xmodmap
xrdb -merge ~/.Xresources

# xsri --set ~/Pictures/Erio1-xmonad.jpg --center-x
# display -window root ~/Pictures/`ls ~/Pictures/ | sort -R | head -n 1` &
display -window root ~/media/pictures/wallpaper.jpg


urxvtd -f -q -o
# ibus-daemon --xim &
a-config setup chromium &

exec xmonad
