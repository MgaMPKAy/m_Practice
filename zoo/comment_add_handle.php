<?php
require_once('zoo-inc.php');

$article_id = $_POST['article_id'];
try {
	comment_add($article_id, $_POST['comment']);
	echo '<body background="/mga-zoo/images/v.png/">';
	echo '评论成功<br />';
	echo build_article_url($article_id, "返回");
}
catch (Exception $e) {
	echo '<body background="/mga-zoo/images/v.png/">';
	echo "一定是哪里出错了<br/>";
	echo $e->getMessage();
}
?>