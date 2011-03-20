<?php
@ $email=$_POST['email'];
@ $username=$_POST['username'];
@ $passwd=$_POST['passwd'];
@ $passwd2=$_POST['passwd2'];

session_start();

if (isset($_POST['user_id']) && isset($_POST['user_passwd'])) {
	$user_id = $_POST['user_id'];
	$user_passwd = $_POST['user_passwd'];

	$db = new mysqli('localhost', 'mysql', 'mysql', 'zoo');

	if (mysqli_connect_errno()) {
		echo 'Connection to database failed:'.
			mysqli_connect_error();
		exit();
	}

	$query = 'SELECT user_id, user_passwd FROM Users'
		."WHERE user_id='$user_id'"
		." AND WHERE user_passwd=sha1('$user_passwd')";
	
	$result = $db->query($query);
	if ($result->num_rows > 0) {
		$_SESSION['valid_user'] = $user_id;
		$db->close();
		$msg = "登录失败";
		//header("Location:home.php");
	} else {
		$db->close();
		$msg = "登录失败";
	}
}
?>
<html>
  <head>
    <title>登录ZOO</title>
  </head>
  <body>
    <h1>登录<strike>QQ</strike>ZOO<strike>NE</strike>帐号</h1>
    <form method='post' action="<?php echo $_SERVER["PHP_SELF"];?>" >
      <?php echo $msg; ?>
      <?php echo "H"; ?>
      <p><strong>用户名</strong><br/>
      <input type='text' name='user_name'></p>
      <p><strong>密码</strong><br/>
      <input type='password' name='user_passwd'></p>
      <p><input type='submit' name='submit' value='GO'></p>
    </form>
  </body>
</html>