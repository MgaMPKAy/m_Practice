<?php
require_once('db-common.php');

function get_name_by_id($user_id)
{
	$db = connect_db();
	
	$query = 'SELECT user_name FROM Users '
		."WHERE user_id = $user_id";
	$result = $db->query($query);
	if ($result) {
		$row = $result->fetch_row();
		$user_name = $row[0];
		$db->close();
		return $user_name;
	} else {
		$db->close();
		return NULL;
	}
}