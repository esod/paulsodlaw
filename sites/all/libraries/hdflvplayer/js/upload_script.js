function streamerl(streamername)
{       
    if(streamername=="none")
    {
         
        document.getElementById("youtube").disabled=false;
        document.getElementById("ffmpeg").disabled=false;
        document.getElementById('stream_url').style.display='none';
        document.getElementById("upload").disabled=false;
        document.getElementById('stream').value = 'none';
    }

    if(streamername=="lighttpd")
    {
        document.getElementById('customurl').style.display = "block";
        document.getElementById('ffmpeg_path').style.display = "none";
        document.getElementById('youtube_url').style.display = "none";
        document.getElementById('upload_path').style.display = "none";
        document.getElementById('stream_url').style.display='none';
        document.getElementById("url").checked=true;
        document.getElementById("youtube").disabled=true;
        document.getElementById("ffmpeg").disabled=true;
        document.getElementById("upload").disabled=true;
        document.getElementById('stream').value = 'lighttpd';
        document.getElementById('radiobutton').value= 'url';
            
           
    }
    else if(streamername=="rtmp")
    {
               
        document.getElementById('customurl').style.display = "block";
        document.getElementById('ffmpeg_path').style.display = "none";
        document.getElementById('youtube_url').style.display = "none";
        document.getElementById('upload_path').style.display = "none";
        document.getElementById('stream_url').style.display='block';
        document.getElementById('url').checked=true; 
        document.getElementById("ffmpeg").disabled=true;
        document.getElementById("youtube").disabled=true;
        document.getElementById("upload").disabled=true;    
        document.getElementById('stream').value = 'rtmp';
        document.getElementById('radiobutton').value= 'url';
            
    }
       
}

function t1(t2)
{ 
    if(t2 == "upload" )
    {
        document.getElementById('radiobutton').value= 'upload';
        document.getElementById('upload_path').style.display = "block"        
        document.getElementById('youtube_url').style.display = "none";
        document.getElementById('ffmpeg_path').style.display = "none";
        document.getElementById('customurl').style.display = "none";
    }
    if(t2 == "youtube" ){
        
        document.getElementById('radiobutton').value= 'youtube';
        document.getElementById('upload_path').style.display = "none";
        document.getElementById('youtube_url').style.display = "block";
        document.getElementById('ffmpeg_path').style.display = "none";
        document.getElementById('customurl').style.display = "none";
    }
    if(t2 == "url" ){

        document.getElementById('radiobutton').value= 'url';        
        document.getElementById('customurl').style.display = "block";
        document.getElementById('youtube_url').style.display = "none";
        document.getElementById('ffmpeg_path').style.display = "none";
        document.getElementById('upload_path').style.display = "none";
    }
    if(t2 == "ffmpeg" ){

        document.getElementById('radiobutton').value= 'ffmpeg';
        document.getElementById('customurl').style.display = "none";
        document.getElementById('ffmpeg_path').style.display = "block";
        document.getElementById('youtube_url').style.display = "none";
        document.getElementById('upload_path').style.display = "none";
    }
 
}

function chkbut()
{      
    
    if(document.getElementById('youtube').checked)
    {
        document.getElementById('radiobutton').value = 'youtube';
        document.uploadfiles.submit();
            
    }
    if(document.getElementById('url').checked)
    {
        document.getElementById('custom_url').value = document.getElementById('url_video').value;
        document.getElementById('custom_hd').value = document.getElementById('url_hd').value;
        document.getElementById('custom_image').value = document.getElementById('url_image').value;
        document.getElementById('custom_preimage').value = document.getElementById('url_previmage').value;
        return true;
    }
    document.getElementById('rollvalue').value= path;
    

}

function roll(path)
{    
    if(path == "1" ){
        document.getElementById('preroll').value = '1';       
        document.getElementById('roll_select').style.display = "block" ;
    }
    if(path == "0" ){
        document.getElementById('preroll').value = '0';
        document.getElementById('roll_select').style.display = "none";
    }
}

function selectpre(path)
{ 
    document.getElementById('prerollid').value = path;
}

function postroll(path)
{

    if(path == "1" )    {
       
        document.getElementById('postroll').value = '1';
        document.getElementById('postroll_select').style.display = "block";
    }
    if(path == "0" ){

        document.getElementById('postroll').value = '0';
        document.getElementById('postroll_select').style.display = "none";
    }
}

function selectpost(path)
{
    document.getElementById('postrollid').value = path;
}

function selectplaylist(path)
{
    document.getElementById('playlistid').value = path;
}

function ads(pat)
{

    if(pat == "upload" )
    {
        document.getElementById('file_path').value= 'upload';
        document.getElementById('upload_url').style.display = "block"
        document.getElementById('roll_url').style.display = "none";

    }
    if(pat == "roll" ){

        document.getElementById('roll_url').style.display = "block";
        document.getElementById('upload_url').style.display = "none";
        document.getElementById('filepath').value= 'roll';
    }
}

function youtube(pat){
    
    document.getElementById('youtube-value').value= pat;
}

function cutomurl(name,pat){
  
    if(name == 'url_video'){      
        document.getElementById('custom_url').value= pat;
    }
    if(name == 'url_hd'){
        document.getElementById('custom_hd').value= pat;
    }
    if(name == 'url_image'){
        document.getElementById('custom_image').value= pat;
    }
    if(name == 'url_previmage'){
        document.getElementById('custom_preimage').value= pat;
    }
    
}

