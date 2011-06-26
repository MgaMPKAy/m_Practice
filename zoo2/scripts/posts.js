$(document).ready(function () {
    //$("inner-content2").css("opacity", 0)
    //	.animate({opacity: 1}, 1500);
    
    $("#content ul li").click(function() {
	$(this).fadeOut(200).fadeIn(200);
    });
    load_inner("my_post", "inner-content");

});

function load_inner(which, to_where)
{
    var xmlhttp = create_xhr();
    var url = "/zoo/ajax-inner/"+which+".php?t=" + new Date().getTime();
    var script_url = "/zoo/scripts/inner/" + which + ".js";
    var user_id = get_page_owner_id();
    
    xmlhttp.onreadystatechange = function(){
	if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
	    var new_page = xmlhttp.responseText;
	    document.getElementById(to_where).innerHTML =  new_page;
	    $.getScript(script_url);
	}
    }
    xmlhttp.open("POST", url , true);
    xmlhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;");
    xmlhttp.send("user_id=" + user_id);
}
