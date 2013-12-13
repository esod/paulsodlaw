/*
 *function for up down description in player page.
*/
$(document).ready(function(){
    $("p").slideDown();
    $('.down').hide();
    $(".up").click(function(){
        $('.up').hide();
        $('.down').show();
        $("p").slideUp();
    });
    $(".down").click(function(){
        $('.down').hide();
        $('.up').show();
        $("p").slideDown();
    });
});

/*
 *function for change playlist in player page.
*/
var http = false;
if(navigator.appName == "Microsoft Internet Explorer") {
    http = new ActiveXObject("Microsoft.XMLHTTP");
} else {
    http = new XMLHttpRequest();
}

function playlistname(pid) {
    
    var path = window.Drupal.settings.basePath;
    var pagearray = path+'node/'+pid+'/videoid';
    if(pid != ''){        
        http.abort();
        http.open("GET", pagearray, true);
        http.onreadystatechange=function() {
            if(http.readyState == 4) {
                var id = http.responseText;
                window.open(path+'hdflvplayer-gallery/'+id+'/'+pid,'_self',false);
            }
        }
        http.send(null);
    }
    else{
        window.open(path+'hdflvplayer-gallery/','_self',false);
    }

}
/*
 *function for get title and description from player.
*/
function currentvideo(id,title,descr){
    document.getElementById('video_title').innerHTML=title;
    document.getElementById('descriptionp').innerHTML=descr;
   
}


  