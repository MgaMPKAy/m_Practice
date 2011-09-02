<?php
$path='/var/www/lighttpd/zoo/php/';
ini_set('include_path', $path);

require_once('comments.php');
require_once('db-common.php');
require_once('login.php');
require_once('logout.php');
require_once('log.php');
require_once('users.php');
require_once('moods.php');
require_once('posts.php');
require_once('register.php');
require_once('validate.php');
?>
