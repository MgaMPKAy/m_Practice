<?php
require_once("zoo-inc.php");

try {
	$mood = $_POST['mood'];
	$mood_id = mood_add($mood);
	log_add(2, $mood_id);
	echo $mood;
}
catch (Exception $e) {
	echo $e->getMessage();
}

?>