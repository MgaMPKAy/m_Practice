<?php
require_once("include.php");
try {
	if (!is_anyone_logined() || !isset($_GET["user_id"])){
		header("Location:./login.php");
	}
	@ $page_user_id = $_GET['user_id'];
	@ $page_user_name = get_name_by_id($page_user_id);
}
catch (Exception $e) {
	echo $e->getMessage();
}
?>
<html>
  <head>
    <link href="./styles/zoo-home.css" rel="stylesheet" type="text/css" />
    <script src="./scripts/jquery.js"></script>
    <script src="./scripts/zoo-home.js"></script>
    <script type="text/javascript">
      //set_cookie("user_id", 2, 30)
      //switch_to("home", 0);
    </script>
  </head>
  <body id="top-body">
    <div id="top-header">
      <h1><?php echo $page_user_name; ?>的空间</h1>
      <hr />
      <ul id="top-menu">
	<li><a href="javascript:switch_to('home', 500)">主页</a></li>
	<li><a href="javascript:switch_to('posts', 500)">日志</a></li>
	<li><a href="javascript:switch_to('photos', 500)">相册</a></li>
	<li><a href="javascript:switch_to('message_board', 500)">留言板</a></li>
	<li><a href="javascript:switch_to('infocenter', 500)">个人中心</a></li>
      </ul>
      <div id="top-other-menu">
	<!-- 登录用户的菜单 -->
      </div>
    </div>
    <div id="top-container">
      <!-- AJAX返回内容 -->
    </div>
    <!--
	<div id="top-footer">
	<hr />
	<p><em>Amazing</em><p>
	</div>
    -->
  </body>
</html>