<?php
require_once("db-common.php");
require_once("login.php");

function mood_add($mood)
{
	$db = connect_db();

	$user_id = $_COOKIE['user_id'];

	date_default_timezone_set('Asia/Hong_Kong');
	$datetime = date("Y-m-d g:i:s");
	
	$query = 'INSERT INTO Moods VALUES('
		."NULL, '$user_id', '$mood', '$datetime')";
	$result = $db->query($query);
	if ($db->affected_rows == 0)
		throw new Exception ("邪恶的错误!!!");

	$query = 'SELECT mood_id FROM Moods '
		."WHERE time = '$datetime'";
	$result = $db->query($query);
	$row = $result->fetch_row();
	$mood_id = $row[0];
	return $mood_id;
}

function get_mood_content($mood_id)
{
	$db = connect_db();
	
	$query = 'SELECT * FROM Moods '
		."WHERE mood_id = '$mood_id'";
	$result = $db->query($query);
	$row = $result->fetch_assoc();
	return $row;
}

function get_mood_ids($user_id, $count)
{
	$db = connect_db();

	$query = 'SELECT mood_id FROM Moods '
		."WHERE user_id = '$user_id'"
		."ORDER BY time DESC ";
	//TODO  $query shuld be sorted by datatime , limit
	$result = $db->query($query);
	
	if (!$result) {
		throw new Exception ("MOOD ID ERROR");
		exit();
	}
	$mood_ids = array();
	for ($i = 0; $i < $count && $row = $result->fetch_row(); $i++)
		$mood_ids[] = $row[0];
	$db->close();
	return $mood_ids;
}