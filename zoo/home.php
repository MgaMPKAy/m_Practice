<?php
require_once('zoo-inc.php');
try {
	if (!is_anyone_logined())
		throw new Exception ("没<a href=./login_form.php>登录</a>");
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
      textarea#mood_input {
      background-color : #EFE;
      width : 500px;
      height: 40px;
      }
    </style>
    <script src="/mga-zoo/scripts/moods.js"></script>
  </head>
  <?php
    echo '<body background="/mga-zoo/images/v.png/">';
    echo "<h1><mark>".$page_user_name."</mark>的个人主页</h1>";
    if ($page_user_id != $logined_user_id) {
	    echo "<a href='./follow_handle.php'>关注</a>";
    }
    echo "<p>最近心情: ";
    if (!empty($recent_mood)) {
	    echo "<span id='mood_show'><b>{$recent_mood['mood']}</b></sapn></p>";
    } else {
	    echo "<span id='mood_show'><b></b></sapn></p>";
    }
    if ($page_user_id == $logined_user_id) {
	    //echo "<form method='post' action='mood_add_handle.php'>";
	    //echo "<form>";
	    echo "<textarea id='mood_input' autofocus='true' maxlength='50'>say something</textarea>";
	    echo '<p><input type="button" value="发布心情" onclick="add_mood_show()"/><br/></p>';
	    //echo "</form>";
	    echo "<a href=./article_add_form.php>写日志</a>";
    }
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