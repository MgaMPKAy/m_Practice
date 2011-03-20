<?php
function valid_email($email)
{
	if (!filter_input(INPUT_POST, 'user_email', FILTER_VALIDATE_EMAIL)) {
		return TRUE;
	} else {
		return TRUE;
	}
}
?>
