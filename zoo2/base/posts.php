<?php
require_once("include.php");

function get_post_ids($user_id, $count)
{
	$db = connect_db();

	$query = 'SELECT post_id FROM Posts '
		."WHERE user_id = '{$user_id}' "
		."ORDER BY post_id DESC ";

	$result = $db->query($query);
	$post_ids = array();
	
	for ($i = 0; $i < $count && $row = $result->fetch_row(); $i++)
		$post_ids[] = $row[0];
	$db->close();
	return $post_ids;
}

function get_post_assoc($post_id)
{
	$db = connect_db();

	$query = 'SELECT * FROM Posts '
		."WHERE post_id = '$post_id'";
	
	if (!($result = $db->query($query)))
		throw new Exception ("数据库查询错误");
	if (!($row = $result->fetch_assoc()))
		throw new Exception ("数据库查询错误");

	$db->close();
	return $row;
}

function new_post($title, $content, $permission)
{
	$db = connect_db();
	
	$user_id = $_COOKIE['user_id'];
	
	date_default_timezone_set('Asia/Hong_Kong');
	$datetime = date("Y-m-d g:i:s");
	
	$query = 'INSERT INTO Posts '
		.'VALUES ('
		."NULL, '{$user_id}', '{$title}', '{$content}', '{$permission}', "
		."'{$datetime}', "
		." NULL, NULL)";
	$result = $db->query($query);
	
	if ($db->affected_rows == 0)
		throw new Exception ("保存日志失败");
	
	$post_id = NULL;
	$query = 'SELECT post_id FROM Posts '
		."WHERE time = '{$datetime}' "
		."AND user_id = '{$user_id}'";
	
	if ($result = $db->query($query)) {
		if ($result->num_rows != 0) {
			$row = $result->fetch_assoc();
			$post_id = $row['post_id'];
		} else {
			throw new Exception ("出错了, 无法获得post_id");
		}
	} else {
		throw new Exception ("出错了, 无法获得post_id");
	}
	$db->close();

	return $post_id;
}

function del_post($post_id)
{
	$db = connect_db();
	$query = 'DELETE FROM Posts '
		."WHERE post_id = '{$post_id}'";
	$result = $db->query($query);
	if ($db->affected_rows == 0)
		throw new Exception ("日志删除失败"); // Not necessary
	$db->close();
}

function update($post_id, $title, $content, $permission)
{
	$db = connect_db();
	$query = "UPDATE Posts "
		."SET title = '{$title}'"
		."SET permission = '{$permission}'"
		."SET content = '{$content}'";
	$result = $db->query($query);

	if ($db->affected_rows == 0)
		throw new Exception("日志修改失败");
	$db->close();
}

function get_article_ower_id($post_id)
{
	$post = get_posr_assoc($post_id);
	return $post['user_id'];
}