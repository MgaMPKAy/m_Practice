function add_mood_show()
{	 
    var mood = document.getElementById("mood_input").value;
    if (mood == "" || mood == " ")
	return;
    if (window.XMLHttpRequest) {
	xmlhttp = new XMLHttpRequest();
    } else {
	xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    
    xmlhttp.onreadystatechange=function()
    {
	if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
	    document.getElementById("mood_show").innerHTML =  "<b style='background-color:yellow'>" + xmlhttp.responseText + "</b>";
	    document.getElementById("mood_input").value = "";
	    setTimeout("document.getElementById('mood_show').innerHTML =  '<b>' + xmlhttp.responseText + '</b>'", 2500);
	}
    }
    xmlhttp.open("POST", "./mood_add_handle.php?time_stamp=" + new Date().getTime(), true);
    xmlhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;");
    xmlhttp.send("mood=" + mood);
}
