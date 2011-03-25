<?php
include_once('db-common.php');

// pri
function valid_name_md5ed_passwd($user_name, $user_passwd)
{
	$db = connect_db();
	
	$query = 'SELECT user_id FROM Users '
		."WHERE user_name = \"$user_name\" "
		."AND user_passwd = \"$user_passwd\" ";
	$result = $db->query($query);
	$rows = $result->fetch_row();
	$db->close();
	return $rows[0];
}

function valid_id_md5ed_passwd($user_id, $user_passwd)
{
	$db = connect_db();
	
	$query = 'SELECT user_name FROM Users '
		."WHERE user_id = \"$user_id\" "
		."AND user_passwd = \"$user_passwd\" ";
	$result = $db->query($query);
	$rows = $result->fetch_row();
	$db->close();
	return $rows[0];
}

// public 
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

function login_with_name($user_name, $user_passwd)
{
	$db = connect_db();
	/*
	if (is_anyone_logined($db))
		throw new Exception ('已经经登录了');
	*/
	$user_id = valid_name_md5ed_passwd($user_name, md5($user_passwd));
	if (!$user_id)
		throw new Exception ('登录失败，用户名或密码不正确');
	$db->close();
	
	setcookie("user_id", $user_id,
		  time() + 60 * 60 * 24 * 30);
	setcookie("user_passwd", md5($user_passwd),
		  time() + 60 * 60 * 24 * 30);
	/* setcookie("user_name", $user_name,
		  time() + 60 * 60 * 24 * 30);
	*/
	return $user_id;
}

function valid_user_id($user_id)
{
	$db = connect_db();
	
	$query = 'SELECT user_id FROM Users '
		."WHERE user_id = $user_id";
	
	$result = $db->query($query);
	if ($result)
		return TRUE;
	else
		return FALSE;
}

// of no use
function check_user_name($user_name)
{
	$db = connect_db();
	
	$query = 'SELECT user_name FROM Users'
		."$user_name";
	$result = $db->query($query);

	
	if ($result)
		return TRUE;
	else
		return FALSE;
}

function get_id_form_name_passwd($user_name, $user_passwd)
{
	$db = connect_db();
	
	$query = 'SELECT user_id FROM Users '
		."WHERE user_name = \"$user_name\" "
		."AND user_passwd = \"$user_passwd\" ";
	$result = $db->query($query);
	$rows = $result->fetch_row();
	$db->close();
	return $rows[0];
}
?>
