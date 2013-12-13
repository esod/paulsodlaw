/*
 *function for upload videos.
*/
$(function(){

    var stream = $('input[name=streameroption]:checked').val();
    $('#stream').val(stream);

    var file = $('input[name=agree]:checked').val();
    $('#radiobutton').val(file);

    var path = window.Drupal.settings.basePath;

    var substr = path.split('/');

    var btnUpload=$('#upload_video');
    var status=$('#video_status');
    new AjaxUpload(btnUpload, {
        action: path+'/admin/hdflvplayer/videos/uploadvideo',
        name: 'uploadfile',
        onSubmit: function(file, ext){
            if (! (ext && /^(mp4|Mp4|m4v|M4V|m4a|M4A|flv|Flv|mp3|MP3|mov|Mov|f4v|F4V)$/.test(ext))){
                // extension is not allowed
                status.text('Only mp3,MP3,flv, FLV, mp4, MP4 , m4v, M4V, M4A, m4a, MOV, mov, mp4v, Mp4v, F4V, f4v files are allowed');
                return false;
            }
            status.text('Uploading...');
        },
        onComplete: function(file, response){
            //On completion clear the status
            status.text('');
            //Add uploaded file to list
            if(response=="success"){
                $('#upload_video').hide();
                $('#retrive_video').hide();
                $('#normalvideoform-value').val(file);
                                    
                $('<li></li>').appendTo('#video_files').html('<span></span><lable id="upload_file">'+file+'</lable>').addClass('success');
            } else{
                $('<li></li>').appendTo('#video_files').text(file).addClass('error');
            }
        }
    });

});

/*
 *function for upload hd videos.
*/
$(function(){

    var path = window.Drupal.settings.basePath;

    var substr = path.split('/');

    var btnUpload=$('#hd_video');
    var status=$('#hd_status');
    new AjaxUpload(btnUpload, {
        action: path+'/admin/hdflvplayer/videos/uploadhd',
        name: 'uploadfile',
        onSubmit: function(file, ext){
            if (! (ext && /^(mp4|Mp4|m4v|M4V|m4a|M4A|flv|Flv|mp3|MP3|mov|Mov|f4v|F4V)$/.test(ext))){
                // extension is not allowed
                status.text('Only mp3,MP3,flv, FLV, mp4, MP4 , m4v, M4V, M4A, m4a, MOV, mov, mp4v, Mp4v, F4V, f4v files are allowed');
                return false;
            }
            status.text('Uploading...');
        },
        onComplete: function(file, response){
            //On completion clear the status
            status.text('');
            //Add uploaded file to list
            if(response=="success"){
                $('#hd_video').hide();
                $('#retrive_hd').hide();
                $('#hdvideoform-value').val(file);

                $('<li></li>').appendTo('#hd_files').html('<span></span><lable id="upload_file">'+file+'</lable>').addClass('success');
            } else{
                $('<li></li>').appendTo('#hd_files').text(file).addClass('error');
            }
        }
    });

});
/*
 *function for upload thumb image.
*/
$(function(){

    var path = window.Drupal.settings.basePath;

    var substr = path.split('/');

    var btnUpload=$('#thumb');
    var status=$('#thumb_status');
    new AjaxUpload(btnUpload, {
        action: path+'/admin/hdflvplayer/videos/uploadthumb',
        name: 'uploadfile',
        onSubmit: function(file, ext){
            if (! (ext && /^(jpg|png|jpeg|gif)$/.test(ext))){
                // extension is not allowed
                status.text('Only jpg, png or gif files are allowed');
                return false;
            }
            status.text('Uploading...');
        },
        onComplete: function(file, response){
            //On completion clear the status
            status.text('');
            //Add uploaded file to list
            if(response=="success"){
                $('#thumb').hide();
                $('#retrive_thumb').hide();
                $('#thumbimageform-value').val(file);

                $('<li></li>').appendTo('#thumb_files').html('<span></span><lable id="upload_file">'+file+'</lable>').addClass('success');
            } else{
                $('<li></li>').appendTo('#thumb_files').text(file).addClass('error');
            }
        }
    });

});

/*
 *function for upload ffmpeg video.
*/
$(function(){

    var file = $('input[name=streameroption]:checked').val();
    $('#stream').val(file);

    var file = $('input[name=agree]:checked').val();
    $('#radiobutton').val(file);

    var path = window.Drupal.settings.basePath;

    var substr = path.split('/');

    var btnUpload=$('#ffmpeg_video');
    var status=$('#ffmpeg_status');
    new AjaxUpload(btnUpload, {
        action: path+'/admin/hdflvplayer/videos/uploadhd',
        name: 'uploadfile',
        onSubmit: function(file, ext){
            if (! (ext && /^(mp4|Mp4|m4v|M4V|m4a|M4A|flv|Flv|mp3|MP3|mov|Mov|f4v|F4V)$/.test(ext))){
                // extension is not allowed
                status.text('Only mp3,MP3,flv, FLV, mp4, MP4 , m4v, M4V, M4A, m4a, MOV, mov, mp4v, Mp4v, F4V, f4v files are allowed');
                return false;
            }
            status.text('Uploading...');
        },
        onComplete: function(file, response){
            //On completion clear the status
            status.text('');
            //Add uploaded file to list
            if(response=="success"){
                $('#ffmpeg_video').hide();
                $('#ffmpegform-value').val(file);

                $('<li></li>').appendTo('#ffmpeg_files').html('<span></span><lable id="upload_file">'+file+'</lable>').addClass('success');
            } else{
                $('<li></li>').appendTo('#ffmpeg_files').text(file).addClass('error');
            }
        }
    });

});
var path = $('input[name=agree]:checked').val();
t1(path);

var pre = $('input[name=preroll]:checked').val();
roll(pre);

var post = $('input[name=postroll]:checked').val();
postroll(post);
