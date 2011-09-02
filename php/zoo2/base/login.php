<?php
require_once("include.php");

function login_with_name($user_name, $user_passwd)
{
	$db = connect_db();
	
	$user_id = valid_name_md5ed_passwd($user_name, md5($user_passwd));
	if (!$user_id)
		throw new Exception ('登录失败，用户名或密码不正确');
	$db->close();
	
	setcookie("user_id", $user_id,
		  time() + 60 * 60 * 24 * 30);
	setcookie("user_passwd", md5($user_passwd),
		  time() + 60 * 60 * 24 * 30);
	setcookie("user_name", $user_name,
		  time() + 60 * 60 * 24 * 30);
	return $user_id;
}

function is_anyone_logined()
{
	$db = connect_db();
	$valid = FALSE;
	if (isset($_COOKIE)
	    && isset($_COOKIE['user_id'])
	    && isset($_COOKIE['user_passwd'])) {
		$valid = valid_id_md5ed_passwd($_COOKIE['user_id'],
					       $_COOKIE['user_passwd']);
		$db->close();
		return $valid;
	}
	return FALSE;
}
?>