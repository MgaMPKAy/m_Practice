<?php
include('zoo-inc.php');

if (is_anyone_logined())
	logout();
echo "<p>退出成功</p>";
header("Location:/mga-zoo/index.php");
?>