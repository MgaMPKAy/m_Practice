<?php
include_once('db-common.php');
include_once('login.php');

function logout()
{
	$db = connect_db();
	
	if (!is_anyone_logined()) {
		$db->close();
		exit();
	}
	setcookie("user_id", NULL,
		  time() - 3600);
	setcookie("user_passwd", NULL,
		  time() -3600);
	$db->close();
	return TRUE;
}
?>
