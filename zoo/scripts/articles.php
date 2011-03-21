<?php
include_once('db-common.php');
include_once('login.php');
	     
function article_add($title, $content, $permission)
{
	$db = connect_db();
	
	if (!is_anyone_logined())
		throw new Exception("还没登录呢");

	$user_id = $_COOKIE('user_id');
	
	$query = 'INSERT INTO Articles'
		.'VALUES ('
		."NULL, $user_id, $title, $text, $permission,"
		."date()"
		.'NULL, NULL)';
	$result = $db->query($query);
	if ($result->affected_rows
	$result->free();
	$db->close();
}