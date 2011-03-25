<?php
function valid_email($email)
{
	if (!filter_VAR($email, FILTER_VALIDATE_EMAIL)) {
		return FALSE;
	} else {
		return TRUE;
	}
}

function valid_name_input($input)
{
	if (!preg_match("/[^a-zA-Z0-9]+$/s", $input))
		return TRUE;
	else
		return FALSE;
}
?>