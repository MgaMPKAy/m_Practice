<?php
include('zoo-inc.php');
$user_email=$_POST['user_email'];
$user_name=$_POST['user_name'];
$user_passwd=$_POST['user_passwd'];
$user_passwd2=$_POST['user_passwd2'];

if (!isset($_POST)) {
	exit;
}
try {
	if (!filled_out($_POST)) {
		throw new Exception('请正确填写全部注册信息');
	}
	if (!valid_email($user_email)) {
		throw new Exception('email的格式不对哦');
	}
	if ($user_passwd != $user_passwd2) {
		throw new Exception('二次密码不一样哦....');
	}
	if ((strlen($user_passwd) < 6)) {
		throw new Exception('6位都不到的密码不给力啊');
	}
	if (( strlen($user_passwd) > 16)) {
		throw new Exception('密码很给力，不过密码最多16位');
	}
	
	register($user_name, $user_email, $user_passwd);

	$display_block = 
		"<h1>注册属于你的<strike>QQ</strike>Zoo<strike>ne</strike></h1>";
	echo $display_block;
	echo "注册成功!!!<br/>";
	echo "<a href='about.php'>完善个人信息</a><br/>";
	echo "<a href='home.php'>查看个人主页</a><br/>";
	
	try {
		login_with_name($user_name, $user_passwd);
	}
	catch (Exception $e){
		echo $e->getMessage();
	}
	//$_SESSION['vaild_user_name'] = $user_name;
}
catch (Exception $e) {
	$display_block = 
		"<h1>注册属于你的<strike>QQ</strike>Zoo<strike>ne</strike></h1>";
	echo $display_block;
	echo "<h2>注册失败了</h2>";
	echo $e->getMessage()."<br />";
	echo "<a href='register_form.php'>再来一次试试</a>";
	exit();
}
?>
