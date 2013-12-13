<?php

// $Id: hdflvplayer_editplaylist.inc,v 1.0 Created by Vasanth at 2010/01/20 15:41:29 Exp $
/*
 * This file is used to edit the ads details.
 */
/* * ****************************************************** HDFLV Playlist Edit Form ************************************************************************ */
/*
 * Edit playlist from elements.
 */
function hdflvplayer_ads_edit_form(&$form_state, $pid, $id=null) {

    if ($pid != '') {
        $result = db_fetch_array(db_query('SELECT * FROM {hdflvplayerads} WHERE id = "%s"', $pid));
    }
    if ($result['filepath'] == 'upload') {
        $upload = 'checked';
    } elseif ($result['filepath'] == 'roll') {
        $roll = 'checked';
    }

    /* Add css an js */

    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/ajaxupload.3.5.js', 'external', 'footer');
    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/jquery-1.3.2.js', 'external', 'footer');
    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/upload_script.js', 'external', 'footer');
    drupal_add_js(drupal_get_path('module', 'hdflvplayer') . '/js/roll.js', 'external', 'footer');

    drupal_add_css(drupal_get_path('module', 'hdflvplayer') . '/style/hdflvplayeradsadd.css');

    $form = array();

    $form['#attributes'] = array('name' => 'uploadfiles', 'onsubmit' => 'return chkbut()');

    /* set the form elements for ads. */

    $form['#prefix'] =
            '<script type="text/javascript">                
ads("' . $result['filepath'] . '");</script><div id="file_path">
    <span class="title">File Path :</span><input type="radio"  ' . $upload . ' name="agree" id="upload" value="upload" onClick="ads(this.value)" /><lable>File</lable>
    <input type="radio" name="agree" id="roll" value="roll"  ' . $roll . ' onClick="ads(this.value)" /> <lable>URL</lable>
    </div>

<div id="roll_url" style="display:none"><tr>
            <th scope="row"><lable>Preroll/Postroll Url :</lable></th>
            <td><input type="text" size="50" name="roll_value" id="roll_value" onchange="rollval(this.value)" value=' . $result['postvideopath'] . '>
                <br /><p>Here you need to enter the URL to the video file
              </td>
        </tr></div>

<div id="upload_url">
<div id="uploadff" ><span>Upload File<span></div></div><div id ="message_url"><span id="status" ></span>
		<ul id="files" ></ul></div>
</div>';

    /* set the hidden values to store the database. */

    $form['hiddenfile'] = array(
        '#prefix' => '<input type="hidden" name="normalvideoform-value" id="normalvideoform-value" value=""  />
                     <input type="hidden" name="upload_path" id="upload_path" value="" />
                     <input type="hidden" size="50" name="filepath" id="filepath" value="" />,
                     <input type="hidden" size="50" name="rollvalue" id="rollvalue" value=""/>',
        '#type' => 'hidden',
        '#name' => 'id',
        '#id' => 'idvalue',
        '#value' => $pid,
    );

    $form['adsname'] = array(
        '#type' => 'textfield',
        '#value' => $result['adsname'],
        '#title' => t('Ad Name'),
    );

    $form['targeturl'] = array(
        '#type' => 'textfield',
        '#value' => $result['targeturl'],
        '#title' => t('Target url'),
    );

    $form['clickurl'] = array(
        '#type' => 'textfield',
        '#value' => $result['clickurl'],
        '#title' => t('Click Hits'),
    );

    $form['impressionurl'] = array(
        '#type' => 'textfield',
        '#value' => $result['impressionurl'],
        '#title' => t('Impression Hits'),
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

/* * ************************************** HDFLV Playlist Edit Form submit *********************************************************************************** */
/*
 * Edt playlist from elements submit function.
 */

function hdflvplayer_ads_edit_form_submit($form, &$form_state) {

    /* check the video path is uploaded or url. */

    if ($form_state['clicked_button']['#post']['rollvalue'] != '') {

        $postvideoPath = trim($form_state['clicked_button']['#post']['rollvalue']);
    } else {
        $postvideoPath = trim($form_state['clicked_button']['#post']['upload_path']);
    }

    $filePath = trim($form_state['clicked_button']['#post']['filepath']);

    $adsName = trim($form_state['clicked_button']['#post']['adsname']);

    $targetUrl = trim($form_state['clicked_button']['#post']['targeturl']);

    $clickUrl = trim($form_state['clicked_button']['#post']['clickurl']);

    $impressionUrl = trim($form_state['clicked_button']['#post']['impressionurl']);

    $published = $form_state['clicked_button']['#post']['published'];

    $id = $form_state['clicked_button']['#post']['id'];

    /* database query for update the values into database. */

    db_query("update {hdflvplayerads} SET published = '" . $published . "', adsname = '" . $adsName . "', filepath = '" . $filePath . "', postvideopath = '" . $postvideoPath . "'
     , targeturl = '" . $targetUrl . "' ,clickurl = '" . $clickUrl . "' , impressionurl = '" . $impressionUrl . "'   where id='" . $id . "'");

    /* Set message after update the values into database. */

    drupal_set_message(t('Ad Updated Successfully'));

    /* Set Redirect path after update the values into database. */

    $form_state['redirect'] = 'admin/hdflvplayer/videos/ads';
}
