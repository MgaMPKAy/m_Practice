<?php
require_once('include.php');

function valid_name_md5ed_passwd($user_name, $user_passwd)
{
	$db = connect_db();

	$query = 'SELECT user_id FROM Users '
		."WHERE user_name = '{$user_name}' "
		."AND user_passwd = '{$user_passwd}' ";
	
	$result = $db->query($query);
	$rows = $result->fetch_assoc();
	$db->close();
	return $rows['user_id'];
}

function valid_id_md5ed_passwd($user_id, $user_passwd)
{
	$db = connect_db();
	
	$query = 'SELECT user_name FROM Users '
		."WHERE user_id = '{$user_id}' "
		."AND user_passwd = '{$user_passwd}' ";

	$result = $db->query($query);
	$rows = $result->fetch_assoc();
	$db->close();
	return $rows['user_name'];
}

function valid_user_id($user_id)
{
	$db = connect_db();
	
	$query = 'SELECT user_id FROM Users '
		."WHERE user_id = {$user_id}";
	
	$result = $db->query($query);
	if ($result->num_rows > 0)
		return TRUE;
	else
		return FALSE;
}

function valid_user_name_input($user_name)
{
	if (!preg_match("/[^a-zA-Z0-9]+$/s", $user_name))
		return TRUE;
	else
		return FALSE;
}

function valid_user_email_input($user_email)
{
	if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
		return FALSE;
	} else {
		return TRUE;
	}
}

function user_name_token($user_name)
{
	$db = connect_db();
		
	$query = 'SELECT user_name FROM Users '
		."WHERE user_name = {$user_name}";
	
	$result = $db->query($query);
	if ($result->num_rows > 0)
		return TRUE;
	else
		return FALSE;
}

function user_email_token($user_email)
{
	$db = connect_db();
		
	$query = 'SELECT user_email FROM Users '
		."WHERE user_email = {$user_email}";
	
	$result = $db->query($query);
	if ($result->num_rows > 0)
		return TRUE;
	else
		return FALSE;
}