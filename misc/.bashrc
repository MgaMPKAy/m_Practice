# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
alias ex='emacsclient -nc $@ -a ""'
alias et='emacsclient -nw $@ -a ""'
alias cex='export LC_CTYPE=zh_CN.UTF-8; emacs'
alias x='startx'
alias chromium='chromium --user-data-dir=/tmp/chromium'
alias poweroff='a-poweroff'
alias network-restart='sudo /etc/rc.d/network restart'
alias a-mixer-mid='amixer set Master 32 > /dev/null'
alias gv='gv --fullscreen --widgetless'

PS1='\[\e[1;31m\]λ\[\e[0m\] '

export GTK_IM_MODULE=ibus
export XMODIFIERS=@im=ibus
export QT_IM_MODULE=ibus

export EDITOR=vim

#export GTK_IM_MODULE_FILE=/etc/gtk-2.0/gtk.immodules

export TRANSMISSION_HOME=/tmp/tmproot/etc/transmission