<html>
  <head>
    <title>新日志</title>
    <style>
      
    </style>
  </head>
  <body>
  <?php
    include('zoo-inc.php');
    if (!is_anyone_logined()) {
	    echo "<p>还没登录了,先"
		    ."<a href='login_form.php'>登录</a>吧</p>";
    } else {
  ?>
  <h1>新Zoo日志</h1>
    <form method="post" action="article_add_handle.php">
      <p>标题<br/>
      <input type="text" name="article_title" maxlength="50"/></p>
      <p>内容<br/>
      <textarea row="80" cols="80" name="text"></textarea>
      </p>
      <p>
      <input type="submit" value="保存" /><br/></p>
    </form>
    <?php
      }
    ?>
  </body>
</html>