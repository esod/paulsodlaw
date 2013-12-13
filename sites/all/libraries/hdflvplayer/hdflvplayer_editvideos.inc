<?php

// $Id: hdflvplayer_profiles.inc,v 1.0 Created by Vasanth at 2010/01/13 11:10:29 Exp $
/*
 * This file is used to edit the video details.
 */
/* * ****************************************************** HDFLV VIDEO FORM ************************************************************************ */
/*
 * Edit videos from elements.
 */
function hdflvplayer_video_edit_form(&$form_state, $pid, $id=null) {

    if ($pid != '') {
        $result = db_fetch_array(db_query('SELECT * FROM {hdflvplayerupload} WHERE id = "%s"', $pid));
    }

    /* Call css and js. */

    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/ajaxupload.3.5.js', 'external', 'footer');
    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/jquery-1.3.2.js', 'external', 'footer');
    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/upload_script.js', 'external', 'footer');
    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/videoadd.js', 'external', 'footer');

    drupal_add_css(drupal_get_path('module', 'hdflvplayer') . '/style/hdflvplayeradd.css');

    /* Call playlist function to retrive the playlists. */

    $playList = hdflvplayer_playlist_get_configs();

    $playList[0] = "None";

    /* playlist Select box. */

    foreach ($playList as $key => $play) {
        if ($key == $result['playlistid']) {
            $playKey = "value = $key selected=selected";
        } else {
            $playKey = "value = $key";
        }

        $playListval .= '<option ' . $playKey . ' >' . $play . '</option>';
    }

    /*
     * Define form as array because it contain the form values and passed to submit function.
     */
    $form = array();

    $youtubeDisplay = "";

    $uploadDisplay = "";

    $urlDisplay = "";

    $adRoll = hdflvplayer_ad_roll();

    if ($adRoll != '') {

        foreach ($adRoll as $key => $ads) {
            if ($key == $result['prerollid']) {
                $preKey = "value = $key selected=selected";
            } else {
                $preKey = "value = $key";
            }
            if ($key == $result['postrollid']) {
                $postKey = "value='.$key.' selected=selected";
            } else {
                $postKey = "value='.$key.'";
            }
            $preAds .= '<option ' . $preKey . ' >' . $ads . '</option>';
            $postAds .= '<option ' . $postKey . ' >' . $ads . '</option>';
        }
    }

    /* Define radio button value. */

    $radioButton = $result['filepath'];

    /* If filepath upload. check upload button and make upload display-block. */ if ($result['filepath'] == 'upload') {

        $youtubeDisplay = "display:none;";

        $uploadDisplay = "display:block;";

        $urlDisplay = "display:none;";

        $upload = 'checked';
    }

    /* If filepath youtube. check youtube button and make youtube display-block. */ else if ($result['filepath'] == 'youtube') {

        $youtubeDisplay = "display:block;";

        $uploadDisplay = "display:none;";

        $urlDisplay = "display:none;";

        $youtube = 'checked';
    }

    /* If filepath url. check url button and make url display-block. */ else if ($result['filepath'] == 'url') {

        $youtubeDisplay = "display:none;";

        $uploadDisplay = "display:none;";

        $urlDisplay = "display: block;";

        $url = 'checked';
    }

    /* If filepath url. check url button and make url display-block. */ else if ($result['filepath'] == 'ffmpeg') {

        $youtubeDisplay = "display:none;";

        $uploadDisplay = "display:none;";

        $urlDisplay = "display: none;";

        $ffmpeg = 'checked';
    }
    /* If streameroption none. check none button. */

    if ($result['streameroption'] == 'none') {
        $none = 'checked';
    }

    /* If streameroption lighttpd. check lighttpd button. */ else if ($result['streameroption'] == 'lighttpd') {
        $lighttpd = 'checked';
    }

    /* If streameroption rtmp. check rtmp button. */ else if ($result['streameroption'] == 'rtmp') {
        $rtmp = 'checked';
    }
    if ($result['postrollads'] == '1') {
        $enablePost = 'checked';
    } else {
        $disablePost = 'checked';
    }
    if ($result['prerollads'] == '1') {
        $enablePre = 'checked';
    } else {
        $disablePre = 'checked';
    }
    if ($result['islive'] == '1') {
        $isliveYes = 'checked';
    } else {
        $isliveNo = 'checked';
    }

    /*     * ********************************************************** Form Fields******************************************************************* */
    $form['#prefix'] =
            '<div style="padding:10px 0;border-top: 1px solid #CCC;margin-top:10px;">
                <span class="title">Streamer option :</span>
                  <input type="radio" name="streameroption" id="stremerOpt1" ' . $none . ' value="none" onclick="streamerl(this.value)" /><lable>None</lable>
                  <input type="radio" name="streameroption" id="stremerOpt2" value="lighttpd" ' . $lighttpd . ' onClick="streamerl(this.value)" /> <lable>lighttpd</lable>
                  <input type="radio" name="streameroption" id="stremerOpt3" value="rtmp" ' . $rtmp . ' onClick="streamerl(this.value)" /> <lable>rtmp</lable>
             </div>

    <div id="file_path">
        <span class="title">File Path :&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
        </span>
            <input type="radio" name="agree" id="upload" value="upload" ' . $upload . ' onClick="t1(this.value)" /><lable> Upload file</lable>
            <input type="radio" name="agree" id="youtube" value = "youtube" ' . $youtube . ' onClick="t1(this.value)" /> <lable>YouTube URL</lable>
            <input type="radio" name="agree" id="url" value = "url" ' . $url . ' onClick="t1(this.value)" /> <lable>Custom URL</lable>
            <input type="radio" name="agree" id="ffmpeg" value= "ffmpeg" ' . $ffmpeg . ' onclick="t1(this.value);"/><lable>FFmpeg</lable>
    </div>

<div id="ffmpeg_path" style="disable:none;">
    <table>
    <tr><th scope="row">Upload Video</th>
         <td>
            <div id="ffmpeg_video" ><span>Upload Video</span></div><div id ="ffmpeg_message_url"><span id="ffmpeg_status" ></span>
		<ul id="ffmpeg_files" ></ul>
            </div>
          </td>
   </tr>
   </table>
</div>


<div id="upload_path" style="' . $uploadDisplay . '">
<table>
     <tr> <th scope="row">Upload Video</th>
                <td width="20%">
                    <div id="upload_video" ><span>Upload Video</span></div><div id ="video_message_url"><span id="video_status" ></span>
		<ul id="video_files" ></ul></div>
 </td><td><div id="retrive_video" class="retrivevalues">' . $result['videourl'] . '</div></td></tr>
            <tr>
            <th scope="row">Upload HD Video(optional)</th>
                <td>
                   <div id="hd_video" ><span>Upload HD Video</span></div><div id ="hd_message_url"><span id="hd_status" ></span>
		<ul id="hd_files" ></ul></div>
            </td><td><div id="retrive_hd" class="retrivevalues">' . $result['hdurl'] . '</div></td></tr>
            <tr><th scope="row">Upload Thumb Image</th><td>

                   <div id="thumb" ><span>Upload Thumb Image</span></div><div id ="thumb_message_url"><span id="thumb_status" ></span>
		<ul id="thumb_files" ></ul></div>
            </td><td><div id="retrive_thumb" class="retrivevalues">' . $result['thumburl'] . '</div></td></tr>
    </table>
    </div>


<div id="youtube_url" class="inside" style="' . $youtubeDisplay . '">
    <table class="form-table">
        <tr id="youtube_tr">
            <th scope="row">Youtube Link</th>
            <td><input type="text" size="50" name="youtube_value" id="youtube_value" onchange="youtube(this.value)" value="' . $result['videourl'] . '" >
                <br /><p>Here you need to enter the URL to the video file
            <br />It accept also a Youtube link:
http://www.youtube.com/watch?v=tTGHCRUdlBs</p></td>
        </tr>
    </table>
</div>

<div id="stream_url" style="display:none">
    <table>
        <tr id="stream_path" name="stream_path" ><td><span class="title">Streamer Path:</span></td>
            <td>
                <input type="text" name="streamname"  id="streamname" style="width:300px" maxlength="250" value=' . $result['streamerpath'] . '>
            </td>
        </tr>
        <tr id="islive_visible" name="islive_visible">
            <td><span class="title">Is Live:</span></td>
            <td>
                <input type="radio" name="islive[]"  id="islive1"   value="0" ' . $isliveNo . '>No
                <input type="radio" name="islive[]"  id="islive2"  value="1" ' . $isliveYes . '>Yes
            </td>
        </tr>
    </table>
</div>

 <div id="customurl" class="inside" style="' . $urlDisplay . '">
                <table class="form-table" style="margin:0px;">
                    <tr>
                        <th scope="row">URL to video file</th>
                        <td><input type="text" size="50" name="url_video" id="url_video" value="' . $result['videourl'] . '"/>
                            <br /><p>Here you need to enter the URL to the video file</p>
                        </td></tr>
                        <tr><th scope="row">URL to HD video file(optional)</th>
                        <td><input type="text" size="50" name="url_hd" id="url_hd" value="' . $result['hdurl'] . '"/>
                            <br /><p>Here you need to enter the URL to the HD video file</p>
                        </td>
                    </tr>
                     <tr><th scope="row">URL to Thumb image file</th>
                        <td><input type="text" size="50" name="url_image" id="url_image" value="' . $result['thumburl'] . '"/>
                            <br /><p>Here you need to enter the URL to the image file</p>
                        </td>
                    </tr>
                    <tr><th scope="row">URL to Thumb Preview image file(Optional)</th>
                        <td><input type="text" size="50" name="url_previmage" id="url_previmage" value="' . $result['previewurl'] . '"/>
                            <br /><p>Here you need to enter the URL to the Preview image file</p>
                        </td>
                    </tr>
                </table>
            </div>


<div id="ads">
<div id="roll">
    <span class="title" >Preroll:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
    </span>
    <input type="radio" name="preroll" id="preroll1"  value="1" ' . $enablePre . ' onclick="roll(this.value)" /><lable>Enable</lable>
    <input type="radio" name="preroll" id="preroll12" ' . $disablePre . ' value="0" onClick="roll(this.value)" /> <lable>Disable</lable>
</div>

<div id="roll_select" style="display:none">
     <tr>
        <span class="title" >Preroll Ads:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
        <td><select id="preroll_id" onChange="selectpre(this.value)"><option value="">Select</option>' . $preAds . '</select>
          </td>
    </tr>
</div>


<div>
    <span class="title">Postroll:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
    <input type="radio" name="postroll" id="postroll1"  value="1" ' . $enablePost . ' onclick="postroll(this.value)" /><lable>Enable</lable>
    <input type="radio" name="postroll" id="postroll2" ' . $disablePost . ' value="0" onClick="postroll(this.value)" /> <lable>Disable</lable>
</div>

<div id="postroll_select" style="display:none">
   <tr>
      <span class="title" >Postroll Ads:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
        <td><select id="postroll_id" onChange="selectpost(this.value)"><option value="">Select</option>' . $postAds . '</select>
          </td>
    </tr>
 </div>

</div>
<div id="playlist"> <span class="title" >Select Playlist:&nbsp;&nbsp;&nbsp;&nbsp;</span>
<select id="playlist_id" name="playlist_id" onChange="selectplaylist(this.value)">' . $playListval . '</select></div>
';

    $form['#attributes'] = array('name' => 'uploadfiles', 'onsubmit' => 'return chkbut()');

    /* set the hidden values to store the database. */

    $form['hiddenfile'] = array(
        '#prefix' => '<input type="hidden" name="normalvideoform-value" id="normalvideoform-value" value=""  />
                     <input type="hidden" name="hdvideoform-value" id="hdvideoform-value" value="" />
                     <input type="hidden" name="thumbimageform-value" id="thumbimageform-value" value="" />
                     <input type="hidden" name="previewimageform-value" id="previewimageform-value" value="" />
                     <input type="hidden" name="ffmpegform-value" id="ffmpegform-value" value="" />
                    <input type="hidden" name="youtube-value" id="youtube-value"  value="" />
                    <input type="hidden" name="customurl" id="custom_url"  value="" />
                    <input type="hidden" name="customhd" id="custom_hd"  value="" />
                    <input type="hidden" name="customimage" id="custom_image"  value="" />
                    <input type="hidden" name="custompreimage" id="custom_preimage"  value="" />
                    <input type="hidden" name="radiobutton" id="radiobutton"  value=' . $radioButton . '/>
                    <input type="hidden" name="stream" id="stream"  value="none" />
                    <input type="hidden" name="preroll" id="preroll"  value="" />
                    <input type="hidden" name="postroll" id="postroll"  value="" />
                    <input type="hidden" name="prerollid" id="prerollid"  value="" />
                    <input type="hidden" name="postrollid" id="postrollid"  value="" />
                    <input type="hidden" name="playlistid" id="playlistid"  value="" />
                    <input type="hidden" name="fileoption" id="fileoption"  value="none" />',
        '#type' => 'hidden',
        '#name' => 'id',
        '#id' => 'idvalue',
        '#value' => $pid,
    );


    $form['title'] = array(
        '#title' => t('Title'),
        '#type' => 'textfield',
        '#name' => 'title',
        '#id' => 'title',
        '#required' => TRUE,
        '#value' => $result['title'],
    );

    $form['description'] = array(
        '#title' => t('Description'),
        '#type' => 'textarea',
        '#name' => 'description',
        '#id' => 'description',
        '#value' => $result['description'],
    );

    $form['targeturl'] = array(
        '#title' => t('Target Url'),
        '#type' => 'textfield',
        '#name' => 'targeturl',
        '#id' => 'targeturl',
        '#value' => $result['targeturl'],
    );


    $form['order'] = array(
        '#title' => t('Order'),
        '#type' => 'textfield',
        '#name' => 'order',
        '#id' => 'order',
        '#size' => '10',
        '#value' => $result['ordering'],
    );

    $form['download'] = array(
        '#type' => 'radios',
        '#title' => t('Download'),
        '#default_value' => $result['download'],
        '#options' => array('1' => t('Enable'), '0' => t('Disable')),
    );

    $form['published'] = array(
        '#type' => 'radios',
        '#title' => t('Published'),
        '#default_value' => $result['published'],
        '#options' => array('1' => t('Enable'), '0' => t('Disable')),
        '#required' => TRUE,
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );

    return $form;
}

/* * ************************************ handles the submit of an individual profile form********************************************************** */
/*
 * Edit videos from elements submit function.
 */

function hdflvplayer_video_edit_form_submit($form, &$form_state) {

    /* get the values from post. */

    $playlistId = $form_state['clicked_button']['#post']['playlistid'];

    $published = $form_state['clicked_button']['#post']['published'];

    $title = addslashes($form_state['clicked_button']['#post']['title']);

    $videos = $form_state['clicked_button']['#post']['videos'];

    $ffmpeg = $form_state['clicked_button']['#post']['ffmpeg'];

    $ffmpegVideos = $form_state['clicked_button']['#post']['ffmpeg_videos'];

    $ffmpegThumbimages = $form_state['clicked_button']['#post']['ffmpeg_thumbimages'];

    $ffmpegPreviewimages = $form_state['clicked_button']['#post']['ffmpeg_previewimages'];

    $ffmpegHd = $form_state['clicked_button']['#post']['ffmpeg_hd'];

    $duration = $form_state['clicked_button']['#post']['duration'];

    $download = $form_state['clicked_button']['#post']['download'];

    $postrollAds = $form_state['clicked_button']['#post']['postroll'];

    $prerollAds = $form_state['clicked_button']['#post']['preroll'];

    $postrollId = $form_state['clicked_button']['#post']['postrollid'];

    $prerollId = $form_state['clicked_button']['#post']['prerollid'];

    $targetUrl = $form_state['clicked_button']['#post']['targeturl'];

    $description = addslashes($form_state['clicked_button']['#post']['description']);

    $ordering = $form_state['clicked_button']['#post']['order'];

    $streamerOption = $form_state['clicked_button']['#post']['stream'];

    $id = $form_state['clicked_button']['#post']['id'];

    /*
     * If radiobutton value is youtube make thumnail and preview image.
     */
    if ($form_state['clicked_button']['#post']['radiobutton'] == 'youtube') {

        $ytb_pattern = "@youtube.com\/watch\?v=([0-9a-zA-Z_-]*)@i";
        $filePath = 'youtube';
        if (preg_match($ytb_pattern, stripslashes($_POST['youtube-value']), $match)) {

            /* Get youtube details. */

            $youtube_data = hd_GetSingleYoutubeVideo($match[1]);

            if ($youtube_data) {
                $thumbUrl = "thumburl= '" . $youtube_data['thumbnail_url'] . "', previewurl= '" . $youtube_data['thumbnail_url'] . "',";
            }

            $videoUrl = "videourl= '" . $form_state['clicked_button']['#post']['youtube-value'] . "',";
            $hdUrl = '';
        } else {
            drupal_set_message(t('Please enter a A Valid YouTube URL!'));
        }
    }

    /* If radiobutton value is url. */

    if ($form_state['clicked_button']['#post']['radiobutton'] == 'url') {

        if ($form_state['clicked_button']['#post']['customurl'] == '') {
            drupal_set_message(t('Enter A Valid URL!'));
        } else {

            $videoPath = $form_state['clicked_button']['#post']['customurl'];

            if ($videoPath != '') {
                $videoUrl = "videourl= '" . $videoPath . "',";
            }

            $hdPath = $form_state['clicked_button']['#post']['customhd'];

            if ($hdPath != '') {
                $hdUrl = "hdurl= '" . $hdPath . "',";
            }

            $thumbPath = $form_state['clicked_button']['#post']['customimage'];

            if ($thumbPath != '') {

                $previewPath = $form_state['clicked_button']['#post']['custompreimage'];

                if ($previewPath != '') {

                    $previewUrl = $previewPath;
                }

                $thumbUrl = "thumburl= '" . $thumbPath . "', previewurl= '" . $previewUrl . "',";
            }

            $filePath = 'url';
        }
    }

    /* If radiobutton value is ffmpeg. */

    if ($_POST['radiobutton'] == 'ffmpeg') {

        $video = url() . '/sites/default/files/hdflvplayer/hdvideos/';

        $fileName = $_POST['ffmpegform-value'];

       $ffmpeg_path = variable_get('hdflvplayer_ffmpeg', '').'ffmpeg.exe';

        $file = explode('.', $fileName);

        $imgPath = variable_get('hdflvplayer_ffmpeg', '');

        $destFile = $video . $fileName;

        $jpgResolution = "320x240";

        $targetPath = $file[0] . ".jpeg";

        /*
         *  Convert any type of videos in to flv and get thumb image from frames of video.
         *  Usinf ffmpeg.
         */

        exec($ffmpeg_path . ' -i ' . $destFile . ' -ab 56 -ar 44100 -b 200 -r 15 -s 320x240 -f flv ' . $imgPath . '\finale.flv');

        exec($ffmpeg_path . ' -i ' . $destFile . ' -an -ss 3 -t 00:00:01 -r 1 -y -vcodec mjpeg -f mjpeg ' . $imgPath . '\thumbimage.jpg');

        $ffmpegVideos = $file[0] . ".flv";

        $ffmpegHd = $_POST['ffmpegform-value'];

        $ffmpegThumbimages = $file[0] . ".jpg";

        $ffmpegPreviewimages = $ffmpegThumbimages;

        $filePath = 'ffmpeg';
    }

    /* If radiobutton value is upload. */

    if ($form_state['clicked_button']['#post']['radiobutton'] == 'upload') {

        $videoPath = $form_state['clicked_button']['#post']['normalvideoform-value'];

        if ($videoPath != '') {
            $videoUrl = "videourl= '" . $videoPath . "',";
        }

        $hdPath = $form_state['clicked_button']['#post']['hdvideoform-value'];

        if ($hdPath != '') {
            $hdUrl = "hdurl= '" . $hdPath . "',";
        }

        $thumbPath = $form_state['clicked_button']['#post']['thumbimageform-value'];

        if ($thumbPath != '') {
            $thumbUrl = "thumburl= '" . $thumbPath . "', previewurl= '" . $thumbPath . "',";
        }

        $filePath = 'upload';
    }

    // parse the data out of the form
    /* If radiobutton value is rtmp. */

    if ($form_state['clicked_button']['#post']['stream'] == 'rtmp') {

        $streamerPath = $form_state['clicked_button']['#post']['streamerpath'];

        $isLive = $form_state['clicked_button']['#post']['islive'];
    } else {

        $streamerPath = '';

        $isLive = '';
    }

    /* database query for update the values into database. */

    db_query("update {hdflvplayerupload} SET published = '" . $published . "', title = '" . $title . "',
                  ffmpeg_videos = '" . $ffmpegVideos . "', ffmpeg_thumbimages = '" . $ffmpegThumbimages . "', ffmpeg_previewimages = '" . $ffmpegPreviewimages . "',
                    ffmpeg_hd= '" . $ffmpegHd . "', filepath= '" . $filePath . "',$videoUrl $thumbUrl $hdUrl playlistid= '" . $playlistId . "', duration= '" . $duration . "', ordering= '" . $ordering . "', streamerpath= '" . $streamerPath . "', streameroption= '" . $streamerOption . "', postrollads= '" . $postrollAds . "', prerollads= '" . $prerollAds . "',
                            description= '" . $description . "', targeturl= '" . $targetUrl . "', download= '" . $download . "', prerollid= '" . $prerollId . "', postrollid= '" . $postrollId . "',  islive = '" . $isLive . "'where id= '" . $id . "'");

    /* Set message after update the values into database. */

    drupal_set_message(t('Updated into Database'));

    /* Set Redirect path after update the values into database. */

    $form_state['redirect'] = 'admin/hdflvplayer/videos/list';
}

/* * ********************************************************** Return Youtube single video******************************************************** */

function hd_GetSingleYoutubeVideo($youtube_media) {

    if ($youtube_media == '')
        return;

    $url = 'http://gdata.youtube.com/feeds/api/videos/' . $youtube_media;

    $ytb = hd_ParseYoutubeDetails(hd_GetYoutubePage($url));

    return $ytb[0];
}

/* * ********************************************************* Parse xml from Youtube****************************************************************** */

function hd_ParseYoutubeDetails($ytVideoXML) {

    // Create parser, fill it with xml then delete it
    $yt_xml_parser = xml_parser_create();

    xml_parse_into_struct($yt_xml_parser, $ytVideoXML, $yt_vals);

    xml_parser_free($yt_xml_parser);

    // Init individual entry array and list array

    $yt_video = array();

    $yt_vidlist = array();

    // is_entry tests if an entry is processing

    $is_entry = true;

    // is_author tests if an author tag is processing

    $is_author = false;

    foreach ($yt_vals as $yt_elem) {

        // If no entry is being processed and tag is not start of entry, skip tag
        if (!$is_entry && $yt_elem['tag'] != 'ENTRY')
            continue;

        // Processed tag
        switch ($yt_elem['tag']) {
            case 'ENTRY' :
                if ($yt_elem['type'] == 'open') {

                    $is_entry = true;

                    $yt_video = array();
                } else {

                    $yt_vidlist[] = $yt_video;

                    $is_entry = false;
                }
                break;
            case 'ID' :

                $yt_video['id'] = substr($yt_elem['value'], -11);

                $yt_video['link'] = $yt_elem['value'];

                break;

            case 'PUBLISHED' :

                $yt_video['published'] = substr($yt_elem['value'], 0, 10) . ' ' . substr($yt_elem['value'], 11, 8);

                break;
            case 'UPDATED' :

                $yt_video['updated'] = substr($yt_elem['value'], 0, 10) . ' ' . substr($yt_elem['value'], 11, 8);

                break;
            case 'MEDIA:TITLE' :

                $yt_video['title'] = $yt_elem['value'];

                break;
            case 'MEDIA:KEYWORDS' :

                $yt_video['tags'] = $yt_elem['value'];

                break;
            case 'MEDIA:DESCRIPTION' :

                $yt_video['description'] = $yt_elem['value'];

                break;
            case 'MEDIA:CATEGORY' :

                $yt_video['category'] = $yt_elem['value'];

                break;
            case 'YT:DURATION' :

                $yt_video['duration'] = $yt_elem['attributes'];

                break;
            case 'MEDIA:THUMBNAIL' :
                if ($yt_elem['attributes']['HEIGHT'] == 240) {

                    $yt_video['thumbnail'] = $yt_elem['attributes'];

                    $yt_video['thumbnail_url'] = $yt_elem['attributes']['URL'];
                }
                break;
            case 'YT:STATISTICS' :

                $yt_video['viewed'] = $yt_elem['attributes']['VIEWCOUNT'];

                break;
            case 'GD:RATING' :

                $yt_video['rating'] = $yt_elem['attributes'];

                break;
            case 'AUTHOR' :

                $is_author = ($yt_elem['type'] == 'open');

                break;
            case 'NAME' :
                if ($is_author)
                    $yt_video['author_name'] = $yt_elem['value'];

                break;
            case 'URI' :
                if ($is_author)
                    $yt_video['author_uri'] = $yt_elem['value'];

                break;
            default :
        }
    }

    unset($yt_vals);

    return $yt_vidlist;
}

/* * ************************************************************ Returns content of a remote page************************************************************ */
/* Still need to do it without curl */

function hd_GetYoutubePage($url) {

    // Try to use curl first
    if (function_exists('curl_init')) {

        $ch = curl_init();

        curl_setopt($ch, CURLOPT_URL, $url);

        curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);

        $xml = curl_exec($ch);

        curl_close($ch);
    }
    // If not found, try to use file_get_contents (requires php > 4.3.0 and allow_url_fopen)
    else {
        $xml = @file_get_contents($url);
    }

    return $xml;
}