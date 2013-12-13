<?php

// $Id: hdflvplayer_addvideos.inc,v 1.0 Created by Vasanth at 2010/01/19 11:7:12 Exp $
/*
 * This file is used to add the videos. in the the form of file upload, direct url, youtube url, custom url etc.
 */
/* * ****************************************************** HDFLV Videos Add Form ************************************************************************ */
/*
 * Add videos from elements.
 */
function hdflvplayer_addvideos_form(&$form_state, $pid, $id=null) {

    /* Add css and js. */

    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/ajaxupload.3.5.js', 'external', 'footer');
    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/jquery-1.3.2.js', 'external', 'footer');
    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/upload_script.js', 'external', 'footer');
    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/videoadd.js', 'external', 'footer');

    drupal_add_css(drupal_get_path('module', 'hdflvplayer') . '/style/hdflvplayeradd.css');

    /* Get list of playlist from database */

    $playlist = hdflvplayer_playlist_get_configs();

    /* Get list on ads from database */

    $adRoll = hdflvplayer_ad_roll();

    $playlist[0] = "None";

    $form = array();

    /* set the option values for ads select box. */

    if ($adRoll) {

        foreach ($adRoll as $key => $ads) {

            $Ads .= '<option value=' . $key . '>' . $ads . '</option>';
        }
    }

    /* set the form elements for addvideos. */

    $form['#prefix'] =
            '<div style="padding:10px 0;border-top: 1px solid #CCC;margin-top:10px;" id="video_add">
    <span class="title">Streamer option:</span>
    <input type="radio" name="streameroption" id="stremerOpt1" checked ="checked" value="none" onclick="streamerl(this.value)" /><lable>None</lable>
    <input type="radio" name="streameroption" id="stremerOpt2" value="lighttpd" onClick="streamerl(this.value)" /> <lable>lighttpd</lable>
    <input type="radio" name="streameroption" id="stremerOpt3" value="rtmp" onClick="streamerl(this.value)" /> <lable>rtmp</lable>
</div>

<div id="file_path">
    <span class="title">File Path :&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
    <input type="radio" name="agree" id="upload" value="upload" onClick="t1(this.value)" /><lable> Upload file</lable>
    <input type="radio" name="agree" id="youtube" value="youtube" checked ="checked" onClick="t1(this.value)" /> <lable>YouTube URL</lable>
    <input type="radio" name="agree" id="url" value="url" onClick="t1(this.value)" /> <lable>Custom URL</lable>
    <input type="radio" name="agree" id="ffmpeg" value= "ffmpeg" onclick="t1(this.value);"/><lable>FFmpeg</lable>
</div>

<div id="ffmpeg_path" style="disable:none;">
    <table><tr><th scope="row">Upload Video</th><td>
                <div id="ffmpeg_video" ><span>Upload Video</span></div><div id ="ffmpeg_message_url"><span id="ffmpeg_status" ></span>
		<ul id="ffmpeg_files" ></ul></div>
            </td></tr></table>
</div>

<div id="upload_path" style="display:none;">
    <table>
        <tr id="ffmpeg_disable_new1" name="ffmpeg_disable_new1"> <th scope="row">Upload Video</th>
            <td>
                <div id="upload_video" ><span>Upload Video</span></div><div id ="video_message_url"><span id="video_status" ></span>
		<ul id="video_files" ></ul></div>
            </td></tr>
        <tr id="ffmpeg_disable_new2" name="ffmpeg_disable_new1">
            <th scope="row">Upload HD Video(optional)</th>
            <td>
                <div id="hd_video" ><span>Upload HD Video</span></div><div id ="hd_message_url"><span id="hd_status" ></span>
		<ul id="hd_files" ></ul></div>
            </td></tr>
        <tr id="ffmpeg_disable_new3" name="ffmpeg_disable_new1"><th scope="row">Upload Thumb Image</th><td>
                <div id="thumb" ><span>Upload Thumb image</span></div><div id ="thumb_message_url"><span id="thumb_status" ></span>
		<ul id="thumb_files" ></ul></div>
            </td></tr>
    </table>
</div>

<div id="youtube_url" class="inside">
    <table class="form-table">
        <tr id="youtube_tr">
            <th scope="row">Youtube Link</th>
            <td><input type="text" size="50" name="youtube_value" id="youtube_value" value="" onchange="youtube(this.value)"/>
                <br /><p>Ex :http://www.youtube.com/watch?v=tTGHCRUdlBs</p></td>
         </tr>
    </table>
</div><tr>


<div id="stream_url" style="display:none">
    <table>
        <tr id="stream_path" name="stream_path" ><td><span class="title">Streamer Path:</span></td>
            <td>
                <input type="text" name="streamname"  id="streamname" style="width:300px" maxlength="250" value="" />
            </td>
        </tr>
        <tr id="islive_visible" name="islive_visible">
            <td><span class="title">Is Live:</span></td>
            <td>
                <input type="radio" name="islive[]"  id="islive1"   value="0" />No
                <input type="radio" name="islive[]"  id="islive2"  value="1" />Yes
            </td>
        </tr>
    </table>
</div>


<div id="customurl" class="inside" style="display:none;">
    <table class="form-table" style="margin:0px;">
        <tr>
            <th scope="row">URL to video file:</th>
            <td><input type="text" size="50" name="url_video" id="url_video" onchange="cutomurl(this.name,this.value)"/>
                <br /><p>Here you need to enter the URL to the video file</p>
            </td></tr>
        <tr><th scope="row">URL to HD video file(optional):</th>
            <td><input type="text" size="50" name="url_hd" id="url_hd" onchange="cutomurl(this.name,this.value)"/>
                <br /><p>Here you need to enter the URL to the HD video file</p>
            </td>
        </tr>
        <tr><th scope="row">URL to Thumb image file:</th>
            <td><input type="text" size="50" name="url_image" id="url_image" onchange="cutomurl(this.name,this.value)"/>
                <br /><p>Here you need to enter the URL to the image file</p>
            </td>
        </tr>
        <tr><th scope="row">URL to Thumb Preview image file(Optional):</th>
            <td><input type="text" size="50" name="url_previmage" id="url_previmage" onchange="cutomurl(this.name,this.value)"/>
                <br /><p>Here you need to enter the URL to the Preview image file</p>
            </td>
        </tr>
    </table>
</div>


<div id="ads">
<div id="roll">
    <span class="title" >Preroll:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
    <input type="radio" name="preroll" id="preroll1"  value="1" onclick="roll(this.value)" /><lable>Enable</lable>
    <input type="radio" name="preroll" id="preroll12" checked ="checked" value="0" onClick="roll(this.value)" /> <lable>Disable</lable>
</div>
<div id="roll_select" style="display:none"><tr>
            <span class="title" >Preroll Ads:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
            <td><select id="preroll_id" onChange="selectpre(this.value)"><option value="">Select</option>' . $Ads . '</select>
              </td>
        </tr></div>


<div>
    <span class="title">Postroll:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
    <input type="radio" name="postroll" id="postroll1"  value="1" onclick="postroll(this.value)" /><lable>Enable</lable>
    <input type="radio" name="postroll" id="postroll2" checked ="checked" value="0" onClick="postroll(this.value)" /> <lable>Disable</lable>
</div>
<div id="postroll_select" style="display:none"><tr>
            <span class="title" >Postroll Ads:&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</span>
            <td><select id="postroll_id" onChange="selectpost(this.value)"><option value="">Select</option>' . $Ads . '</select>
              </td>
        </tr></div></div>';

    /* validation. */

    $form['#attributes'] = array('name' => 'uploadfiles', 'onsubmit' => 'return chkbut()');

    /* set the hidden values to store the database. */

    $form['hiddenfile'] = array(
        '#prefix' => '<input type="hidden" name="normalvideoform-value" id="normalvideoform-value" value=""  />
                     <input type="hidden" name="hdvideoform-value" id="hdvideoform-value" value="" />
                     <input type="hidden" name="thumbimageform-value" id="thumbimageform-value" value="" />
                     <input type="hidden" name="previewimageform-value" id="previewimageform-value" value="" />
                     <input type="hidden" name="ffmpegform-value" id="ffmpegform-value" value="" />
                    <input type="hidden" name="youtube-value" id="youtube-value"  value="" />
                    <input type="hidden" name="custom_url" id="custom_url"  value="" />
                    <input type="hidden" name="custom_hd" id="custom_hd"  value="" />
                    <input type="hidden" name="custom_image" id="custom_image"  value="" />
                    <input type="hidden" name="custom_preimage" id="custom_preimage"  value="" />
                    <input type="hidden" name="radiobutton" id="radiobutton"  value="" />
                    <input type="hidden" name="stream" id="stream"  value="none" />
                    <input type="hidden" name="preroll" id="preroll"  value="" />
                    <input type="hidden" name="postroll" id="postroll"  value="" />
                    <input type="hidden" name="prerollid" id="prerollid"  value="" />
                    <input type="hidden" name="postrollid" id="postrollid"  value="" />
                    <input type="hidden" name="fileoption" id="fileoption"  value="none" />',
        '#type' => 'hidden',
        '#name' => 'file1',
        '#id' => 'normalvideoform-value',
        '#value' => 'video1',
    );

    $form['title'] = array(
        '#title' => t('Title'),
        '#type' => 'textfield',
        '#name' => 'title',
        '#id' => 'title',
        '#value' => '',
        '#required' => TRUE,
    );

    $form['description'] = array(
        '#title' => t('Description'),
        '#type' => 'textarea',
        '#name' => 'description',
        '#id' => 'description',
        '#value' => '',
    );

    $form['targeturl'] = array(
        '#title' => t('Target Url'),
        '#type' => 'textfield',
        '#name' => 'targeturl',
        '#id' => 'targeturl',
        '#value' => '',
    );

    $form['playlistid'] = array(
        '#title' => t('Select Playlist'),
        '#type' => 'select',
        '#options' => $playlist,
        '#default_value' => $playlist[0],
    );
    $form['order'] = array(
        '#title' => t('Order'),
        '#type' => 'textfield',
        '#name' => 'order',
        '#id' => 'order',
        '#size' => '10',
        '#value' => '',
    );

    $form['download'] = array(
        '#type' => 'radios',
        '#title' => t('Download'),
        '#default_value' => 1,
        '#options' => array('1' => t('Enable'), '0' => t('Disable')),
    );

    $form['published'] = array(
        '#type' => 'radios',
        '#title' => t('Published'),
        '#default_value' => 1,
        '#options' => array('1' => t('Enable'), '0' => t('Disable')),
        '#required' => TRUE,
    );

    $form['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Submit')
    );

    return $form;
}

/* * ***************************************** HDFLV Videos Add Form submit *********************************************************************************** */
/*
 * Add videos from elements submit function.
 */

function hdflvplayer_addvideos_form_submit($form, &$form_state) {

    /* set addslashes for title to avoid single quotes and double quotes error. */

    $title = addslashes($_POST['title']);

    $playlistId = $_POST['playlistid'];

    $published = $_POST['published'];

    $download = $_POST['download'];

    $postroll = $_POST['postroll'];

    $postrollId = $_POST['postrollid'];

    $preroll = $_POST['preroll'];

    $prerollId = $_POST['prerollid'];

    $targetUrl = $_POST['targeturl'];

    /* set addslashes for description to avoid single quotes and double quotes error. */

    $description = addslashes($_POST['description']);

    $order = $_POST['order'];

    $streamerOption = $_POST['stream'];

    $published = $_POST['published'];

    /* If the file path is youtube. */

    if ($_POST['title'] != '') {

        if ($_POST['radiobutton'] == 'youtube') {

            $ytb_pattern = "@youtube.com\/watch\?v=([0-9a-zA-Z_-]*)@i";

            if (preg_match($ytb_pattern, stripslashes($_POST['youtube-value']), $match)) {

                /* Get youtube video details ,preview image, thumb image etc */

                $youtube_data = hd_GetSingleYoutubeVideo($match[1]);

                if ($youtube_data) {

                    $thumbPath = $youtube_data['thumbnail_url'];

                    $previewPath = $youtube_data['thumbnail_url'];
                }

                $videoPath = $_POST['youtube-value'];

                $hdPath = '';

                $filePath = 'youtube';
            } else {

                /* Set error message. */

                drupal_set_message(t('Please enter a A Valid YouTube URL!'));
            }
        }

        /* If the file path is  custom url */

        if ($_POST['radiobutton'] == 'url') {

            if ($_POST['custom_url'] == '') {

                drupal_set_message(t('Enter A Valid URL!'));
            } else {

                $videoPath = $_POST['custom_url'];

                $hdPath = $_POST['custom_hd'];

                $thumbPath = $_POST['custom_image'];

                $previewPath = $_POST['custom_preimage'];

                $filePath = 'url';
            }
        }

        /* If the file path is  upload */

        if ($_POST['radiobutton'] == 'upload') {

            $videoPath = $form_state['clicked_button']['#post']['normalvideoform-value'];

            $hdPath = $form_state['clicked_button']['#post']['hdvideoform-value'];

            $thumbPath = $form_state['clicked_button']['#post']['thumbimageform-value'];

            $previewPath = $thumbPath;

            $filePath = 'upload';
        }

        /* If the file path is  Rtmp */

        if ($_POST['stream'] == 'rtmp') {

            $streamerPath = $_POST['streamerpath'];

            $isLives = $_POST['islive'];

            $isLive = $isLives[0];
        } else {

            $streamerPath = '';

            $isLive = '';
        }

        /* If the file path is  ffmpeg */

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
             * Convert any type of videos in to flv and get thumb image from frames of video.
             * Usinf ffmpeg.
             */

            exec($ffmpeg_path . ' -i ' . $destFile . ' -ab 56 -ar 44100 -b 200 -r 15 -s 320x240 -f flv ' . $imgPath . '\finale.flv');

            exec($ffmpeg_path . ' -i ' . $destFile . ' -an -ss 3 -t 00:00:01 -r 1 -y -vcodec mjpeg -f mjpeg ' . $imgPath . '\thumbimage.jpg');

            $ffmpegVideos = $file[0] . ".flv";

            $ffmpegHd = $_POST['ffmpegform-value'];

            $ffmpegThumbimages = $file[0] . ".jpg";

            $ffmpegPreviewimages = $ffmpegThumbimages;

            $filePath = 'ffmpeg';
        }

        /* database query for insert the values into database. */

        if ($videoPath != '') {

            db_query("INSERT INTO {hdflvplayerupload}  (`published`, `title`,  `ffmpeg_videos`, `ffmpeg_thumbimages`, `ffmpeg_previewimages`, `ffmpeg_hd`, `filepath`, `videourl`, `thumburl`, `previewurl`, `hdurl`, `playlistid`, `duration`, `ordering`, `streamerpath`, `streameroption`, `postrollads`, `prerollads`, `description`, `targeturl`, `download`, `prerollid`, `postrollid`,  `islive`) VALUES
('$published', '$title', '$ffmpegVideos', '$ffmpegThumbimages', '$ffmpegPreviewimages', '$ffmpegHd', '$filePath', '$videoPath', '$thumbPath', '$previewPath', '$hdPath', '$playlistId', '$duration', '$order', '$streamerPath', '$streamerOption', '$postroll', '$preroll', '$description', '$targetUrl', '$download', '$prerollId', '$postrollId', '$isLive');");

            /* Set message after insert the values into database. */

            drupal_set_message(t('Inserted into Database'));

            /* Set Redirect path after insert the values into database. */

            $form_state['redirect'] = 'admin/hdflvplayer/videos/list';
        }
    } else {

        /* Set error message. */

        drupal_set_message(t('Please enter the title!'));
    }
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