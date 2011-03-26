<?php
require_once('zoo-inc.php');
try {
	if (($article_id = $_GET['article_id']) == null)
		throw new Exception("url错误");

	if (!is_anyone_logined())
		throw new Exception("没<a href='./login_form.php'>登录</a>");
	$logined_user_id = $_COOKIE['user_id'];
	
	$article = get_article_content_assoc($article_id);

	if ($article['user_id'] != $logined_user_id)
		throw new Exception("没有编辑权限");
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
    <title><?php echo $article['title']; ?></title>
  </head>
  <body>
    <form method="post" action="article_edit_handle.php">
      <p>标题<br/>
      <input type="text" name="article_title" maxlength="50" value="<?php echo $article['title']; ?>"/></p>
      <p>内容<br/>
      <textarea rows="24" cols="80" name="text"><?php echo $article['text'] ?>
      </textarea><br/></p>
      <p>阅读权限
      <select name='permission'>
	<option value='A'>公开</option>
	<option value='F'>好友</option>
	<option value='N'>私人</option>
      </select></p>
      <input type="hidden" name="article_id" value="<?php echo $article_id; ?>" /> 
      <!-- TODO 有安全问题 -->
      <p><input type="submit" value="保存" /><br/></p>
</form>
</body>
</html>