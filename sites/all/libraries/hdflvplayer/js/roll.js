/*
 *function for upload ads video.
*/
$(function(){

    var file = $('input[name=agree]:checked').val();
    $('#filepath').val(file);

    var path = window.Drupal.settings.basePath;

    var btnUpload=$('#uploadff');

   var status=$('#status');

   new AjaxUpload(btnUpload, {
        action: path+'/admin/hdflvplayer/videos/uploadroll',
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
                $('#upload_url').hide();
                $('#upload_path').val(file);
                $('#rollvalue').val('');
                                    
                $('<li></li>').appendTo('#files').html('<span></span><lable id="upload_file">'+file+'</lable>').addClass('success');
            } else{
                $('<li></li>').appendTo('#files').text(file).addClass('error');
            }
        }
    });

});

$('#roll_value').change(function(){        
    var roll = $('#roll_value').val();
    $('#rollvalue').val(roll);

});


