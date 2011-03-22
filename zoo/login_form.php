<html>
  <head>
    <title>登录Zoo</title>
  </head>
  <body background="/mga-zoo/images/v.png">
    <?php
      include('zoo-inc.php');
      if (is_anyone_logined()) {
	      echo "<p>已经登录了<p>"
		      ."<a href='logout.php'>退出</a>吧</p>";
      } else {
    ?>
    <div style="text-align: center"> 
    <h1>登录</h1>
    <form method=post action=login_handle.php>
      <p>姓名<br/>
      <input type='text' name='user_name' maxlength=20/></p>
      <p>密码<br/>
      <input type='password' name='user_passwd' maxlength=16/></p>
      <p>
	<input type='submit' value='登录' /><br/>
      </p>
      <p>
	<a href='register_form.php'>还没注册Zoo？</a><br/>
	<a href='register_form.php'>忘记重要的Zoo密码？</a>
      </p>
    </form>
    </div>
    <?php
      }
    ?>
  </body>
</html>
