<?php
require_once('db-common.php');
require_once('login.php');

function log_add($type, $target)
{
	$db = connect_db();
	$user_id = $_COOKIE['user_id'];
	if(!is_anyone_logined())
		throw new Exception("没登录");

	$query = 'INSERT INTO Log VALUES('
		."NULL, '$user_id', '$type', '$target')";
	$db->query($query);

	if ($db->affected_rows == 0)
		throw new Exception("Log记录失败");
	$db->close();
}
?>