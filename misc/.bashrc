# ~/.bashrc

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

## Set up lambda prompt
PS1='\[\e[1;31m\]λ\[\e[0m\] '

## Set up aliases
source ~/.bash_aliases

## General env variable
export EDITOR=vim
export BROWSER=chromium

# Special env variable
export KFAT1=/tmp/kfat1
export SETUP_DIR=~/setup

## make use of /tmp/tmproot
export PKG_CONFIG_PATH=/tmp/tmproot/lib/pkgconfig
# export C_INCLUDE_PATH=/tmp/tmproot/include

## for java7
export JAVA_HOME=/tmp/tmproot/lib/jvm/java-7-openjdk
export J2SDKDIR=/tmp/tmproot/lib/jvm/java-7-openjdk
export J2REDIR=/tmp/tmproot/lib/jvm/java-7-openjdk/jre
export _JAVA_AWT_WM_NONREPARENTING=1

## for chromium
export CHROMIUM_USER_FLAGS="--user-data-dir=/tmp/chromium/"

## misc
export TRANSMISSION_HOME=/tmp/tmproot/etc/transmission

## Set up environment variable for input method
# export GTK_IM_MODULE=ibus
# export XMODIFIERS=@im=ibus
# export QT_IM_MODULE=ibus
## uncomment this is if necessary
## export GTK_IM_MODULE_FILE=/etc/gtk-2.0/gtk.immodules

## for tomcat (use a-tomcat instead)
# export CATALINA_HOME=/tmp/tmproot
# export CLASSPATH=".:/tmp/workspace:$CATALINA_HOME/lib/servlet-api.jar"

## for ant
# export ANT_HOME=/tmp/tmproot/share/java/apache-ant
# export PATH=$PATH:$ANT_HOME/bin
