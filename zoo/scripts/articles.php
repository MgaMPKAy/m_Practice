<?php
require_once('db-common.php');
require_once('login.php');
require_once('log.php');

function article_add($title, $content, $permission)
{
	$db = connect_db();
	
	if (!is_anyone_logined())
		throw new Exception("还没登录呢");
	
	$user_id = $_COOKIE['user_id'];
	
	date_default_timezone_set('Asia/Hong_Kong');
	$datetime = date("Y-m-d g:i:s");
	
	$query = 'INSERT INTO Articles '
		.'VALUES ('
		."NULL, '$user_id', '$title', '$content', '$permission', "
		."'$datetime', "
		." NULL, NULL)";
	$result = $db->query($query);
	
	if ($db->affected_rows == 0)
		throw new Exception ("保存日志失败");
	
	$article_id = NULL;
	$query = 'SELECT article_id FROM Articles '
		."WHERE time = '$datetime'";
	
	if ($result = $db->query($query)) {
		if ($result->num_rows != 0) {
			$row = $result->fetch_row();
			$article_id = $row[0];
		} else {
			throw new Exception ("出错了, 无法获得article_id");
		}
	} else {
		throw new Exception ("出错了, 无法获得article_id");
	}
	$db->close();
	
	return $article_id;
}

function article_delete($article_id)
{
	$db = connect_db();
	$query = 'DELETE FROM Articles '
		."WHERE article_id = '$article_id'";
	$result = $db->query($query);
	$db->close();
}
function article_update($article_id, $title, $content, $permission)
{
	
}

function get_article_content_assoc($article_id)
{
	$db = connect_db();

	$query = 'SELECT * FROM Articles '
		."WHERE article_id = '$article_id'";

	if (!($result = $db->query($query)))
		throw new Exception ("数据库查询错误");
	if (!($row = $result->fetch_assoc()))
		throw new Exception ("数据库查询错误");

	$db->close();
	return $row;
}

// of no use

function get_article_ids($user_id, $count)
{
	$db = connect_db();

	$query = 'SELECT article_id FROM Articles '
		."WHERE user_id = $user_id";
	//TODO  $query shuld be sorted by datatime , limit
	$result = $db->query($query);

	$article_ids = array();
	for ($i = 0; $i < $count && $row = $result->fetch_row(); $i++)
		$article_ids[] = $row[0];
	$db->close();
	return $article_ids;
}

function build_article_url($article_id, $article_title)
{
	$url =  "<a href='article_view.php?article_id=$article_id'>"
		."$article_title</a>";
	return $url;
}
			