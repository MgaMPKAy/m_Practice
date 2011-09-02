<?php
require_once("include.php");

try {
	// 检测用户
	if (!is_anyone_logined())
		throw new Exception ("还没登录");
	
	$page_owner_id = $_POST['user_id'];
	$page_user_name = get_name_by_id($page_owner_id);
	$logined_user_id = get_logined_user_id();
}
catch (Exception $e)
{
	echo "error";
	echo $e->getMessage();
}
//处理数据并返回
?>
<div id="content">
  <div id="left">
    <ul id="menu">
      <?php if ($page_owner_id == $logined_user_id) {
      ?>
      <li><a href="javascript:load_inner('new_post', 'inner-content')">写日志</a></li>
      <li><a href="javascript:load_inner('my_post', 'inner-content')">我的日志</a></li>
      <li><a href="javascript:load_inner('friend_post', 'inner-content')">好友日志</a></li>
      <li><a href="javascript:load_inner('manage_post', 'inner-content')">日志管理</a></li>
      <?php } else {
      ?>
      <li><a href="javascript:load_inner('my_post', 'inner-content')">查看日志</a></li>
      <?php }?>
    </ul>
    
  </div>
  <div id="inner-content">
    <b></b>
  </div>
</div>
<div>
  <link href="./styles/posts.css" rel="stylesheet" type="text/css" />
</div>
