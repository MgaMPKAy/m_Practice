function switch_to(where, fade_out_time)
{
    $(document).ready(function(){
	//$("#top-content").fadeOut(fade_out_time);
    });
    
    load_page(where);
    
}

function load_page(where)
{
    var user_id = get_page_owner_id();
    
    var url = "./" + where + ".php?time_stamp=" + new Date().getTime();
    var script_url = "/zoo/scripts/" + where +".js";
    var xmlhttp = create_xhr();
        
    xmlhttp.onreadystatechange = function(){
	if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
	    var new_page = xmlhttp.responseText;
	    document.getElementById('top-container').innerHTML =  new_page;
	    $.getScript(script_url);
	}
    }
    xmlhttp.open("POST", url , true);
    xmlhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded;");
    xmlhttp.send("user_id=" + user_id);
}

function create_xhr()
{
    var xmlhttp;
    
    if (window.XMLHttpRequest) {
	xmlhttp = new XMLHttpRequest();
    } else {
	xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }
    return xmlhttp;
}

function set_cookie(name, value, expiredays)
{
    var ex_day = new Date();
    ex_day.setDate(ex_day.getDate() + expiredays);
    document.cookie = name + "=" + escape(value) +
	((expiredays == null)?"":";expires=" + ex_day.toGMTString())
}

function get_cookie(c_name)
{
    if (document.cookie.length>0) {
	c_start = document.cookie.indexOf(c_name + "=");
	if (c_start!=-1) { 
	    c_start = c_start + c_name.length+1;
	    c_end=document.cookie.indexOf(";", c_start);
	    if (c_end==-1) c_end=document.cookie.length
	    return unescape(document.cookie.substring(c_start,c_end));
	} 
    }
    return ""
}

function get_GET()
{
    var GET = new Array();
    var loc = window.location.toString();

    loc = loc.split('?');
    if (typeof(loc[1]) == 'string') {
	s = loc[1].split('&');
	for (i = 0; i < loc.length; i++) {
	    s = loc[i].split("=");
	    eval('GET["' + s[0] + '"]' + '="' + s[1]+'"');
	}
    }
    return GET;
}

function get_page_owner_id()
{
    var GET = get_GET();
    return GET['user_id'];
}

function get_logined_user_id()
{
    var str = get_cookie("user_id");
    
    return parseInt(str);
}