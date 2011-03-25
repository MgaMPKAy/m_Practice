<?php
require_once("zoo-inc.php");

$mood = $_POST['mood'];
$mood_id = mood_add($mood);
log_add(2, $mood_id);
$user_id = $_COOKIE['user_id'];
echo '<body background="/mga-zoo/images/v.png/">';
echo '<P>心情发布成功</P>';
echo "<a href='./home.php?user_id=$user_id'> 返回</a>"; //TODO AJAX
?>