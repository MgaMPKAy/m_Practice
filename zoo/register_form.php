<html>
  <head>
    <title>注册</title>
  </head>
  <body>
    <?php
      include('zoo-inc.php');
      if (is_anyone_logined()) {
	      echo "<p>已经登录了,先"
		      ."<a href='logout.php'>退出</a>吧</p>";
      } else {
    ?>
    <h1>注册属于你的<strike>QQ</strike>Zoo<strike>ne</strike></h1>
    <form method='post' action='register_handle.php'>
      <p>姓名<br/>
      <input type='text' name='user_name' maxlength=20/></p>
      <p>邮箱<br/>
      <input type='text' name='user_email' maxlength=50/></p>
      <p>密码<br/>
      <input type='password' name='user_passwd' maxlength=16/></p>
      <p>确认密码<br/>
      <input type='password' name='user_passwd2' maxlength=16/></p>
      <p>
      <input type='submit' value='注册' /></p>
    </form>
    <?php
      }
    ?>
  </body>
</html>