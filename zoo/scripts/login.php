<?php
include_once('db-common.php');

function login_with_name($user_name, $user_passwd)
{
	$db = connect_db();
	/*
	if (is_anyone_logined($db))
		throw new Exception ('已经经登录了');
	*/
	if (!valid_name_sha1_passwd($user_name, sha1($user_passwd)))
		throw new Exception ('登录失败...');
	setcookie("user_name", $user_name,
		  time() + 60 * 60 * 24 * 30);
	setcookie("user_passwd", sha1($user_passwd),
		  time() + 60 * 60 * 24 * 30);
	$db->close();
}

function check_user_name($user_name, $db)
{
	$query = 'SELECT user_name FROM Users'
		."$user_name";
	$result = $db->query($query);
		
	if ($result->num_rows > 0)
		return TRUE;
	else
		return FALSE;
}

function valid_name_sha1_passwd($user_name, $user_passwd)
{
	$db = connect_db();
	
	$query = 'SELECT user_name, user_passwd FROM Users '
		."WHERE user_name = \"$user_name\" "
		."AND user_passwd = \"$user_passwd\" ";
	$result = $db->query($query);
	$rows = $result->num_rows;
	$db->close();
	
	if ($rows != 0)
		return TRUE;
	else
		return FALSE;
}

function is_anyone_logined()
{
	$db = connect_db();
	$valid = FALSE;
	if (isset($_COOKIE)
	    && isset($_COOKIE['user_name'])
	    && isset($_COOKIE['user_passwd'])) {
		$valid = valid_name_sha1_passwd($_COOKIE['user_name'],
						 $_COOKIE['user_passwd']);
		$db->close();
		return $valid;
	}
	return FALSE;
}
