#!/bin/bash

PREFIX=/tmp/tmproot

cd /tmp/workspace
wget http://www.php.net/distributions/php-5.4.0.tar.bz2
tar xf php-5.4.0.tar.bz2
cd php-5.4.0
./configure \
--prefix=$PREFIX \
--sbindir=$PREFIX/bin \
--sysconfdir=$PREFIX/etc/php \
--enable-fpm \
--with-config-file-path=$PREFIX/etc/php \
--with-config-file-scan-dir=$PREFIX/etc/php \
--disable-ipv6 \
--with-zlib \
--with-curl \
--with-gd \
--with-jpeg-dir \
--with-png-dir  \
--with-freetype-dir \
--with-gmp \
--enable-mbstring  \
--with-mysqli=mysqlnd \
--with-pdo-mysql=mysqlnd  \
--enable-sysvmsg \
--enable-sysvsem \
--enable-sysvshm \
--with-pear
make && make install

cd /tmp/workspace
wget http://nginx.org/download/nginx-1.0.13.tar.gz
tar xf nginx-1.0.13.tar.gz
cd nginx-1.0.13
./configure \
--prefix=$PREFIX \
--sbin-path=$PREFIX/bin/nginx \
--pid-path=$PREFIX/var/run/nginx-pid \
--lock-path=$PREFIX/var/run/nginx-lock \
--conf-path=$PREFIX/etc/nginx/nginx.conf \
--error-log-path=$PREFIX/var/log/error.log \
--http-log-path=$PREFIX/var/log/access.log \
--http-client-body-temp-path=$PREFIX/var/run/clent-body-temp \
--http-proxy-temp-path=$PREFIX/var/run/proxy-temp \
--http-fastcgi-temp-path=$PREFIX/var/run/fastcgi-temp \
--without-http_scgi_module \
--without-http_uwsgi_module
make && make install
