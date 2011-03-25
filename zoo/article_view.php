<?php
require_once('zoo-inc.php');

$article_id = $_GET['article_id'];
$user_id = $_COOKIE['user_id'];

try {
	$article = get_article_content_assoc($article_id);
	$permission = $article['permission'];
	$article_owner_id = $article['user_id'];
	$comment_ids = get_comment_ids($article['article_id']);
	
	$article['text'] = stripslashes($article['text']);
	echo "<h1>".$article['title']."</h1>";
	echo "<p>".$article['text']."<p><br/>";
	echo "<p><mark>发布于</mark>".$article['time']."<p>";
	echo "<p><a href='./article_edit_form.php?article_id=$article_id' >编辑</a>or"; //TODO AJAX EDIT
	echo "<a href='./article_delete.php?article_id=$article_id' >删除</a></p>";
	echo "<p>评论:</p>";
	// TODO echo article that contain PHP code
	echo "<form method='post' action='comment_add_handle.php'>";
	echo "<textarea cols='80' name='comment' maxlength='512'></textarea>";
	echo "<p><input type='hidden' name='article_id' value='$article_id'></p>";
	echo '<p><input type="submit" value="发表评论" /><br/></p>';
	echo "</form>";
	$i = 1;
	foreach ($comment_ids as $comment_id) {
		$comment = get_comment($comment_id);
		echo "<p>$i : ".$comment['comment']."</p>";
		$i++;
	}
	
}
catch (Exception $e) {
	echo $e->getMessage();
}
?>