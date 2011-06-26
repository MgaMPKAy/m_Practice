$(document).ready(function() {
    $("#inner-content2").css("opacity", 0)
	.animate({opacity: 1}, 1000);
    $("#save").click(save_post);
});

function save_post()
{
    var post_title = document.getElementById("post-title").value;
    var post_content = document.getElementById("post-content").value;
    var post_permission = document.getElementById("post-permission").value;
    
    //alert(post_content)
    var user_id = get_logined_user_id();
    var page_page_ower_id = get_page_owner_id();
    if (user_id != page_page_ower_id)
	return;
    
    var sent_content = "user_id="+user_id+"&title="+post_title +"&content=" + post_content +"&permission" + post_permission;
    
    var xmlhttp = create_xhr();
    var url = "/zoo/script/inner/save_post.php?t=" + new Date().getTime();;
    xmlhttp.onreadystatechange = function(){
	if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
	    var new_page = xmlhttp.responseText;
	    document.getElementById('inner-content2').innerHTML =  new_page;
	    //$.getScript(script_url);
	}
    }
    xmlhttp.open("POST", url , true);
    xmlhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;");
    
    xmlhttp.send(sent_content);
}

