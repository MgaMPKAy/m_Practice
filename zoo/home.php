<?php
require_once('zoo-inc.php');
try {
	if (!is_anyone_logined())
		throw new Exception ("没登录");
	$logined_user_id = $_COOKIE['user_id'];
	
	$page_user_id = $_GET['user_id'];
	if (!valid_user_id($page_user_id))
		throw new Exception ("非法用户ID");
	$page_user_name = get_name_by_id($page_user_id);
	
	$recent_mood_id = get_mood_ids($page_user_id, 1);
	if (!empty($recent_mood_id))
		$recent_mood = get_mood_content($recent_mood_id[0]);
	
	$article_ids = get_article_ids($page_user_id, 100);
	
	//$log =Mysql... get_user_logs($page_user_id, 10);
	
}
catch (Exception $e)
{
	echo '<body background="/mga-zoo/images/v.png/">';
	echo "一定是哪里出错了<br/>";
	echo $e->getMessage();
	exit();
}
?>
<html>
  <head>
    <style>
    </style>
  </head>
  <?php
    echo '<body background="/mga-zoo/images/v.png/">';
    echo "<h1><mark>".$page_user_name."</mark>的个人主页</h1>";
    if (!empty($recent_mood_id)) {
	    echo "<p>最近心情: ".$recent_mood['mood']."</p>";
    }
    echo "<form method='post' action='mood_add_handle.php'>";
    echo "<textarea rows='3' cols='80' name='mood' autofocus='true' >随便说点什么</textarea>";
    if ($page_user_id == $logined_user_id)
	    echo '<p><input type="submit"  value="发布心情" /><br/></p>';
    echo "</form>";
    if ($page_user_id == $logined_user_id)
	    echo "<a href=./article_add_form.php>写日志</a>";
    echo "<p><mark>最新日志:</mark> ";
    if (empty($article_ids)) {
	    echo "还没写过日志呢";
    } else {
	    echo "<br>";
    }
    $i = 1;
    //TODO use  table to show aricles
    foreach($article_ids as $aid) {
	    $article = get_article_content_assoc($aid);
	    $url = build_article_url($aid, $article['title']);
	    echo $i.":". $url.$article['time']."<br/>";
	    $i++;
    }
    echo "</p>";
    ?>
</html>