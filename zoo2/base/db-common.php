<?php
function connect_db()
{
	$db = new mysqli('localhost', 'mysql', 'mysql', 'zoo2');

	if ($db->connect_error) {
		throw new Exception ('Connect Error ('
				     .$db->connect_errno. ')'
				     .$db->connect_error);
	}
	return $db;
}
?>