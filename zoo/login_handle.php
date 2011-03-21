<?php
include('zoo-inc.php');
@ $user_name=$_POST['user_name'];
@ $user_passwd=$_POST['user_passwd'];

if (!isset($_POST)) {
	exit;
}
try {
	if (!filled_out($_POST)) {
		throw new Exception('请正确填写全部注册信息');
	}

	login_with_name($user_name, $user_passwd);
	
	$display_block =
		'<body background="/mga-zoo/images/v.png/">'
		.'<h1>登录Zoo</h1>'
		."<p>登录成功</p>";
	echo $display_block;
	echo "<a href='home.php'>查看个人主页</a><br/>";
	echo "<//bodu>";
	//header("Location：http://localhost/mga-zoo/home.php");
	exit();
}
catch (Exception $e)
{
	$display_block =
		'<body background="/mga-zoo/images/v.png/">'
		.'<h1>登录Zoo</h1>';
	echo $display_block;
	echo $e->getMessage()."<br/>\n";
	echo "<a href='login_form.php'>再来一次试试</a>";
	echo '</bodu>';
}
?>
