<?php
require_once('db-common.php');
require_once('login.php');

function comment_add($article_id, $comment)
{
	if (!is_anyone_logined())
		throw new Exception("登录啊");
	$db = connect_db();

	$user_id = $_COOKIE['user_id'];
	date_default_timezone_set('Asia/Hong_Kong');
	$datetime = date("Y-m-d g:i:s");
	
	$query = 'INSERT INTO Comments VALUES('
		."NULL,'$user_id' ,'$article_id', '$datetime', '$comment')";
	$result = $db->query($query);
	$db->close();
}

// oop maybe better
function get_comment_ids($article_id)
{
	$db = connect_db();
	
	$query = 'SELECT comment_id FROM Comments '
		."WHERE article_id = $article_id";
	$result = $db->query($query);
	$comment_ids = array();

	if ($result)
		while ($rows = $result->fetch_row())
			$comment_ids[] = $rows[0];
	$db->close();
	return  $comment_ids;
}

function get_comment($comment_id)
{
	$db = connect_db();
	
	$query = 'SELECT comment, time FROM Comments '
		."WHERE comment_id = '$comment_id'";
	$result = $db->query($query);
	$row = NULL;
	if ($result)
		$row = $result->fetch_assoc();
	$db->close();
	return $row;
}
