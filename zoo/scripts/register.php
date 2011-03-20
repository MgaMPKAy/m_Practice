<?php
include_once('db-common.php');

function register($user_name, $user_email, $user_passwd)
{
	$db = connect_db();

	/* 检查user_name是否被注册 */
	$query = 'SELECT user_name FROM Users '
		."WHERE user_name='$user_name'";
	
	$result = $db->query($query);
	if (!$result)
		throw new Exception('Could not execute query');
	if ($result->num_rows>0) {
		throw new Exception('真的很对不起，这个用户名已经被注册了...');
	}
	
	/* 检查user_email是否被注册 */
	$query = 'SELECT user_passwd FROM Users '
		."WHERE user_email='$user_email'";
	$result = $db->query($query);
	if (!$result) {
		throw new Exception('Could not execute query');
		if ($result->num_rows>0) {
			throw new Exception('真的很对不起，这个邮箱已经被注册了...');
		}
	}
	/* 记录到数据库 */
	$query = 'INSERT INTO Users '
		.'(user_id, user_name, user_email, user_passwd) VALUES '
		."(NULL, '$user_name', '$user_email', sha1('".$user_passwd."'))";
	$result = $db->query($query);
	if (!$result) {
		throw new Exception('又失败了');
	}
	return true;
}

function filled_out($form_vars) {
	foreach ($form_vars as $key => $value) {
		if ((!isset($key)) || ($value == '')) {
			return false;
		}
	}
		return true;
}
?>
