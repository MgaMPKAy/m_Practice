# ~/.bashrc

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

PS1='\[\e[1;31m\]λ\[\e[0m\] '

# Set up aliases
source ~/.bash_aliases

# Set up environment variable for input method
export GTK_IM_MODULE=ibus
export XMODIFIERS=@im=ibus
export QT_IM_MODULE=ibus
#export GTK_IM_MODULE_FILE=/etc/gtk-2.0/gtk.immodules

export EDITOR=vim

# Special env variable
export TRANSMISSION_HOME=/tmp/tmproot/etc/transmission
export KFAT1=/tmp/KFAT1
