# Bash aliases
# add "source /path/to/this/file" in .bashrc or .bash_profile

# ls
alias lsc='ls --color=auto'
alias lsl='ls -hl'

# emacs
alias ex='emacsclient -nc $@ -a ""'
alias et='emacsclient -nw $@ -a ""'
alias cex='export LC_CTYPE=zh_CN.UTF-8; emacs'
alias a-kill-emacs='killall emacs'

# mixer
alias a-mixer-mute='a-mixer mute'
alias a-mixer-mid='amixer set Master 40 > /dev/null'
alias a-mixer-set="amixer sset Master"
alias a-mixer-get="amixer sget Master"
alias a-mixer-up='a-mixer up'
alias a-mixer-down='a-mixer down'

# config setup & backup
alias a-config-setup-emacs='a-config setup emacs'
alias a-config-backup-emacs='a-config backup emacs'
alias a-config-setup-chromium='a-config setup chromium'
alias a-config-backup-chromium='a-config backup chromium'

# network
alias a-network-restart='sudo /etc/rc.d/network restart'
alias a-router-limit-speed='a-router limit'
alias a-router-unlimit-speed='a-router unlimit'
alias a-router-week-limit='a-router week-limit'
alias a-router-strong-limit='a-router strong-limit'
alias a-router-reboot='a-router reboot'

alias a-vpn-down='sudo killall pppd'
alias a-vpn-tenacy='a-vpn up tenacy'
alias a-vpn-tenacy-fast-unsafe='a-vpn up fast'
alias a-vpn-vpncup='a-vpn up vpncup'

# tmp root
# rm is alias to a-tmp-rm below
alias a-tmproot-clean='/bin/rm /tmp/tmproot/* -rf'
alias a-ld-library-path='export LD_LIBRARY_PATH=/tmp/tmproot/lib'
alias a-ld-run-path='export LD_RUN_PATH=/tmp/tmproot/lib'

# haskell
alias a-cabal='~/.cabal/bin/cabal'
alias a-ln-cabal-dev='mkdir cabal-dev && ln -s /tmp/tmproot/packages-7.4.2.conf ./cabal-dev/packages-7.4.2.conf'
alias cabal-dev='cabal-dev --sandbox=/tmp/tmproot'
alias cabal='echo use a-cabal'
alias ghc-dev='ghc -package-conf/tmp/tmproot/packages-7.4.2.conf'
alias ghci-dev='ghci -package-conf/tmp/tmproot/packages-7.4.2.conf'
alias hugs='hugs +s'

# other
alias :q='exit'
alias a-flood='UdpFlood 7 10 20 60'
alias a-py-http-server='python -m SimpleHTTPServer'
alias a-rm='/bin/rm'
alias a-screenshot='import "/tmp/workspace/screenshot-"$(date +%F-%T)".png"'
alias a-touchpad-enable-middle='xinput set-prop "FSPPS/2 Sentelic FingerSensingPad" "Evdev Middle Button Emulation" 1'
alias a-x11grab='ffmpeg -f x11grab -s 1280x800 -i :0.0 out.mp4'
alias a-xmonad-restart='xmonad --restart'
alias cdw='cd /tmp/workspace/'
alias grep='grep --color=auto'
alias gv='gv --fullscreen --widgetless'
alias mplayer='mplayer -vo xv -ao alsa'
alias poweroff='a-poweroff'
alias rm='a-tmp-rm'
alias x='startx > /tmp/log/Xorg.0.log 2>&1 &'
alias zathura='a-zathura'

# mount
#alias a-mount-u="mkdir /tmp/u && sudo mount -o utf8=1 /dev/sdb1 /tmp/u"
alias a-umount-u="sudo umount /dev/sdb1"

# tmp root bin
alias a-java-7='export JAVA_HOME=/tmp/tmproot/lib/jvm/java-7-openjdk;export J2SDKDIR=/tmp/tmproot/lib/jvm/java-7-openjdk;export J2REDIR=/tmp/tmproot/lib/jvm/java-7-openjdk/jre'
alias geany='geany -c /tmp/tmproot/etc/geany'
alias vbam='vbam -c /tmp/tmproot/etc/vbam.cfg'

# seldom
# alias mplayer-dvd='mplayer -dvd-device /dev/sr0'
# alias ghci='ghci --read-doc-ghci'

# of no use
# alias fsc='mono ~/.bin/FSharp-2.0.0.0/bin/fsc.exe $@'
#alias a-java-6='export JAVA_HOME=/tmp/tmproot/lib/jvm/java-6-openjdk;export J2REDIR=/tmp/tmproot/lib/jvm/java-6-openjdk/jre;export J2SDKDIR=/tmp/tmproot/lib/jvm/java-6-openjdk'
#alias a-ant='export ANT_HOME=/tmp/tmproot/share/java/apache-ant;export PATH=$PATH:$ANT_HOME/bin'
#alias a-tomcat='export CATALINA_HOME=/tmp/tmproot;export CLASSPATH=.:/tmp/workspace:$CATALINA_HOME/lib/servlet-api.jar'
#alias a-play='export PATH=$PATH:/tmp/tmproot/play-2.0'
