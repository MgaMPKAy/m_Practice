<?php
include_once('zoo-inc.php');

$article_title = $_POST['article_title'];
$article_text = $_POST['text'];

try {
	$article_text = "<pre>$article_text</pre>";
	$article_text = addslashes($article_text);
	$article_id = article_add($article_title, $article_text, "A");
	if ($article_id == NULL)
		throw new Exception ("出错了");
	log_add(1, $article_id);
	echo "<h1>新日志</h1>";
	echo "<h2>保存成功</h2>";
	echo "<p><a href='article_view.php?article_id=$article_id'>查看日志</a><p>";
}
catch (Exception $e)
{
	echo "<h1>新日志</h1>";
	echo "<h2>日志保存失败了</h2>";
	echo $e->getMessage()."<br />";
	echo "<a href='article_add_form.php'>再来一次试试</a>";
	exit();
}
?>
