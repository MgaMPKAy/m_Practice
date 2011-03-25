function validate_form()
{
    var x = document.forms["register_form"]["user_name"].value;
    if (x == null || x == '') {
	var err_span = document.createElement("span");
	var err_msg = document.createTextNode("ad");
	err_span.appendChild(err_msg);
	x.appendChild(err_span);
	return false;
    }
}