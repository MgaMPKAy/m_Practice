<?php
require_once('zoo-inc.php');

$article_id = $_GET['article_id'];

try {
	$article = get_article_content_assoc($article_id);
	$comment_ids = get_comment_ids($article['article_id']);
	
	$article['text'] = stripslashes($article['text']);
	echo "<h1>".$article['title']."</h1>";
	echo "<p>".$article['text']."<p><br/>";
	echo "<p>发布于".$article['time']."</p>";
	echo "<p>评论:</p>";
	// TODO echo article that contain PHP code
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