<?php
$path='/var/www/lighttpd/mga-zoo/scripts/';
ini_set('include_path', get_include_path().PATH_SEPARATOR.$path);

include_once('db-common.php');
include_once('register.php');
include_once('validate.php');
include_once('login.php');
?>
