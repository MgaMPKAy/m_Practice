<?php
//session_start();
$display_block =
	"<form method='post' action=\"".$_SERVER['PHP_SELF']."\">"
	."<input type=\"text\" name='name' />"
	."<input type=\"submit\" Value='submit' />"
	."</form>";
if (isset($_POST)) {
	setcookie("id", $_POST['name'], -1);
}
?>

<html>
  <body>
    <?php echo $display_block; ?>
    <?php
      if (isset($_POST)) {
	     echo $_COOKIE['id'];
    }?>
  </body>
</html>