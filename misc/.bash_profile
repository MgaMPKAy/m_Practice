#
# ~/.bash_profile
#

[[ -f ~/.bashrc ]] && . ~/.bashrc

## Set up $PATH
HOME_BIN_PATH="/home/adlezz/.bin/bin"
#GHC_PATH="/home/adlezz/.bin/ghc/bin/"
GHC_PATH="/tmp/u/ghc/bin"
CABCL_PATH="/home/adlezz/.cabal/bin/"
TMPBIN_PATH="/tmp/tmproot/bin"

export PATH=$TMPBIN_PATH:$PATH:$GHC_PATH:$CABCL_PATH:$HOME_BIN_PATH

## Set up emacs
a-config setup emacs

## I love tmpfs
cd /tmp/workspace/

## Start x if login in tty1
if [[ -z $DISPLAY && $(tty) = /dev/tty1 ]]; then
    a-fast-startx > /tmp/Xorg.0.log 2>&1 &
    # startx > /tmp/Xorg.0.log 2>&1 &
    # Could use xinit instead of startx
    #exec xinit -- /usr/bin/X -nolisten tcp vt7
fi
