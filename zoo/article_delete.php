<?php
require_once('zoo-inc.php');
echo '<html>';
echo '<body background=‘/mga-zoo/images/v.png’>';
echo '<h1>删除日志</h1>';
try {
	if (!isset($_GET))
		throw new Exception("URL出错了");
	@ $article_id = $_GET['article_id'];
	@ $user_id = $_COOKIE['user_id'];
	@ $article_owner_id = get_article_ids($article_id);
	if ($article_owner_id != $user_id)
		throw new Exception("没有删除权限");
	article_delete($article_id);
	
	echo "<p>删除成功</p>";
	echo "<a href=./home.php?user_id=$user_id>返回个人主页</a>";
}
catch (Exception $e)
{
	echo "<p>删除失败</p>";
	echo $e->getMessage();
}