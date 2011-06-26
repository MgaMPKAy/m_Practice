<?php
require_once('include.php');

function get_name_by_id($user_id)
{
	$db = connect_db();
	
	$query = 'SELECT user_name FROM Users '
		."WHERE user_id = $user_id";
	$result = $db->query($query);
	if ($result) {
		$row = $result->fetch_assoc();
		$user_name = $row['user_name'];
		$db->close();
		return $user_name;
	} else {
		$db->close();
		return NULL;
	}
}

function get_logined_user_id()
{
	if (isset($_COOKIE['user_id']))
		return $_COOKIE['user_id'];
	else
		return 0;
}