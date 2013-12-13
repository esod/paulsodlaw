<?php

// $Id: hdflvplayer_addplaylist.inc,v 1.0 Created by Vasanth at 2010/01/20 15:22:54 Exp $
/*
 * This file is used to add the ads.in the type of url and file upload.
 */
/* * ****************************************************** HDFLV Playlist Add Form ************************************************************************ */
/*
 * Add Ads from elements.
 */
function hdflvplayer_addads_form(&$form_state, $pid, $id=null) {

    /* Add css and js. */

    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/ajaxupload.3.5.js', 'external', 'footer');
    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/jquery-1.3.2.js', 'external', 'footer');
    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/upload_script.js', 'external', 'footer');
    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/roll.js', 'external', 'footer');

    drupal_add_css(drupal_get_path('module', 'hdflvplayer') . '/style/hdflvplayeradsadd.css');

    $form = array();

    /* set the form elements for ads. */

    $form['#attributes'] = array('name' => 'uploadfiles', 'onsubmit' => 'return chkbut()');

    $form['#prefix'] =
            '<div id="file_path">
    <span class="title">File Path :</span><input type="radio" checked ="checked" name="agree" id="upload" value="upload" onClick="ads(this.value)" /><lable>File</lable>
    <input type="radio" name="agree" id="roll" value="roll"  onClick="ads(this.value)" /> <lable>URL</lable>
    </div>

<div id="roll_url" style="display:none"><tr>
            <th scope="row"><lable>Preroll/Postroll Url :</lable></th>
            <td><input type="text" size="50" name="roll_value" id="roll_value" value="" />
                <br /><p>Here you need to enter the URL to the video file
              </td>
        </tr></div>

<div id="upload_url">
<div id="uploadff"><span>Upload File<span></div></div><div id ="message_url"><span id="status" ></span>
		<ul id="files" ></ul></div>
</div>';

    /* set the hidden values to store the database. */

    $form['hiddenfile'] = array(
        '#prefix' => '<input type="hidden" name="normalvideoform-value" id="normalvideoform-value" value=""  />
                     <input type="hidden" name="upload_path" id="upload_path" value="" />
                     <input type="hidden" size="50" name="rollvalue" id="rollvalue" value="" />',
        '#type' => 'hidden',
        '#name' => 'filepath',
        '#id' => 'filepath',
        '#value' => '',
    );

    $form['adsname'] = array(
        '#type' => 'textfield',
        '#title' => t('Ad Name'),
    );

    $form['targeturl'] = array(
        '#type' => 'textfield',
        '#title' => t('Target url'),
    );

    $form['clickurl'] = array(
        '#type' => 'textfield',
        '#title' => t('Click Hits'),
    );

    $form['impressionurl'] = array(
        '#type' => 'textfield',
        '#title' => t('Impression Hits'),
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

/* * ************************************** HDFLV Playlist Add Form submit *********************************************************************************** */
/*
 * Add Ads from elements submit function.
 */

function hdflvplayer_addads_form_submit($form, &$form_state) {

    $published = $form_state['clicked_button']['#post']['published'];

    $adsName = $form_state['clicked_button']['#post']['adsname'];

    if ($form_state['clicked_button']['#post']['rollvalue'] != '') {
        $postvideoPath = $form_state['clicked_button']['#post']['rollvalue'];
    } else {
        $postvideoPath = $form_state['clicked_button']['#post']['upload_path'];
    }

    $filePath = $form_state['clicked_button']['#post']['filepath'];

    $targetUrl = $form_state['clicked_button']['#post']['targeturl'];

    $clickUrl = $form_state['clicked_button']['#post']['clickurl'];

    $impressionUrl = $form_state['clicked_button']['#post']['impressionurl'];

    /* database query for insert the values into database. */

    db_query("INSERT INTO {hdflvplayerads}  (`published`,`adsname`,`filepath`,`postvideopath`,`targeturl`,`clickurl`,`impressionurl`) 
            VALUES ('$published','$adsName','$filePath','$postvideoPath','$targetUrl','$clickUrl','$impressionUrl')");

    /* Set message after insert the values into database. */

    drupal_set_message(t('Playlist Inserted into Database'));

    /* Set Redirect path after insert the values into database. */

    $form_state['redirect'] = 'admin/hdflvplayer/videos/ads';
}

