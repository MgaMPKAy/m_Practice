<?php
require_once('zoo-inc.php');

$new = htmlspecialchars("<a href='test'>Test</a>", ENT_QUOTES);
echo $new;

?>