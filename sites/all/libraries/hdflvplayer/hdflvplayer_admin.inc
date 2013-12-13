<?php

// $Id: hdflvplayer.admin.inc,v 1.0 Created by Vasanth at 2010/01/12 20:22:57 goba Exp $
/*
 * This file is contain form elements of Player configuration, language setting, page setting, google adsense.
 * And these details are stored in table variable in drupal. 
 */
/* * ************************************************************** Manage video function Route Path ************************************************ */
/*
 * Videos List page.
 */
function hdflvplayer_admin() {

    $op = isset($_POST['op']) ? $_POST['op'] : $callback_arg;

    /* select route path. */

    switch ($op) {
        case t('Create new account'):
        case 'create':
            $output = drupal_get_form('hdflvplayer_addvideos_form');
            break;
        default:
            if (!empty($_POST['accounts']) && isset($_POST['operation']) && ($_POST['operation'] == 'delete')) {
                $output = drupal_get_form('user_multiple_delete_confirm');
            } else {
                $output .= drupal_get_form('hdflvplayer_listvideos_form');
            }
    }
    return $output;
}

/* * ************************************************************** PLAYER SETTINGS FORM **************************************************************** */

function hdflvplayer_admin_settings(&$form_state) {

    // Add  the Hdflvplayer administration JS/CSS

    drupal_add_css(drupal_get_path('module', 'hdflvplayer') . '/style/hdflvplayer.css');

    $form['#attributes'] = array('enctype' => "multipart/form-data");
    $form['filedset'] = array('#type' => 'fieldset',
        '#title' => t('HDFLV Player'),
    );

    /* Logo Settings form filelds */

    $form['filedset']['Logo Settings'] = array('#type' => 'fieldset',
        '#title' => t('Logo Settings'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    $form['filedset']['Logo Settings']['hdflvplayer_key'] = array('#type' => 'textfield',
        '#title' => t('Licence Key'),
        '#default_value' => variable_get('hdflvplayer_key', ''),
        '#maxlength' => 50,
        '#size' => 30,
        '#description' => t('<a href="http://hdflvplayer.net/shop/index.php?main_page=product_info&amp;cPath=7&amp;products_id=7" target="_blank"><div class="buy"></div></a>'),
        '#attributes' => array('class' => 'test'),
    );

    $form['filedset']['Logo Settings']['hdflvplayer_logo'] = array('#type' => 'file',
        '#title' => t('Logo'),
        '#default_value' => variable_get('hdflvplayer_logo', ''),
        '#size' => 30,
        '#maxlength' => 50,
    );

    $form['filedset']['Logo Settings']['hdflvplayer_logo_url'] = array('#type' => 'textfield',
        '#title' => t('Logo Url'),
        '#default_value' => variable_get('hdflvplayer_logo_url', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Logo Settings']['hdflvplayer_logo_alpha'] = array('#type' => 'textfield',
        '#title' => t('Logo Alpha'),
        '#default_value' => variable_get('hdflvplayer_logo_alpha', ''),
        '#maxlength' => 30,
        '#size' => 30,
        '#description' => t('Edit the value to have transparancy depth of logo'),
    );

    $form['filedset']['Logo Settings']['hdflvplayer_logo_position'] = array(
        '#type' => 'select',
        '#title' => t('Logo Position'),
        '#default_value' => variable_get('hdflvplayer_logo_position', ''),
        '#options' => array('TR' => t('Top Right'), 'TL' => t('Top Left'), 'LB' => t('Bottom Left'), 'RB' => t('Bottom Right')),
    );

    /* Ads Settings form filelds */

    $form['filedset']['Ads Settings'] = array('#type' => 'fieldset',
        '#title' => t('Ads Settings'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    $form['filedset']['Ads Settings']['hdflvplayer_preroll'] = array(
        '#type' => 'radios',
        '#title' => t('Pre roll ads'),
        '#default_value' => variable_get('hdflvplayer_preroll', ''),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
    );

    $form['filedset']['Ads Settings']['hdflvplayer_postroll'] = array(
        '#type' => 'radios',
        '#title' => t('Post roll ads'),
        '#default_value' => variable_get('hdflvplayer_postroll', ''),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
    );

    $form['filedset']['Ads Settings']['hdflvplayer_random'] = array(
        '#type' => 'radios',
        '#title' => t('Random'),
        '#default_value' => variable_get('hdflvplayer_random', ''),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
    );

    $form['filedset']['Ads Settings']['hdflvplayer_ads'] = array(
        '#type' => 'radios',
        '#title' => t('Google Ads'),
        '#default_value' => variable_get('hdflvplayer_ads', ''),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
    );

    /* Player Settings form filelds */

    $form['filedset']['Player Settings'] = array('#type' => 'fieldset',
        '#title' => t('Player Settings'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    $form['filedset']['Player Settings']['hdflvplayer_width'] = array('#type' => 'textfield',
        '#title' => t('Width'),
        '#default_value' => variable_get('hdflvplayer_width', ''),
        '#maxlength' => 30,
        '#description' => t('Width of the video player in pixel '),
        '#size' => 20,
    );

    $form['filedset']['Player Settings']['hdflvplayer_height'] = array('#type' => 'textfield',
        '#title' => t('Height'),
        '#default_value' => variable_get('hdflvplayer_height', ''),
        '#description' => t('Height of the video player in pixel '),
        '#size' => 20,
        '#maxlength' => 30,
    );

    $form['filedset']['Player Settings']['hdflvplayer_buffer_time'] = array('#type' => 'textfield',
        '#title' => t('Buffer Time'),
        '#default_value' => variable_get('hdflvplayer_buffer_time', ''),
        '#size' => 20,
        '#description' => t('Secs Recommended value is 3'),
        '#maxlength' => 30,
    );

    $form['filedset']['Player Settings']['hdflvplayer_stage_color'] = array('#type' => 'textfield',
        '#title' => t('Stage Color'),
        '#default_value' => variable_get('hdflvplayer_stage_color', ''),
        '#size' => 20,
        '#maxlength' => 30,
    );

    $form['filedset']['Player Settings']['hdflvplayer_login_link'] = array('#type' => 'textfield',
        '#title' => t('Login Page Link'),
        '#default_value' => variable_get('hdflvplayer_login_link', ''),
        '#size' => 20,
        '#maxlength' => 30,
    );

    $form['filedset']['Player Settings']['hdflvplayer_ffmpeg'] = array('#type' => 'textfield',
        '#title' => t('FFMpeg Binary Path'),
        '#default_value' => variable_get('hdflvplayer_ffmpeg', ''),
        '#size' => 30,
        '#maxlength' => 40,
    );

    $form['filedset']['Player Settings']['hdflvplayer_vast_partner'] = array('#type' => 'textfield',
        '#title' => t('Vast Partner Id'),
        '#default_value' => variable_get('hdflvplayer_vast_partner', ''),
        '#size' => 20,
        '#maxlength' => 30,
    );

    $form['filedset']['Player Settings']['hdflvplayer_volume'] = array('#type' => 'textfield',
        '#title' => t('Volume'),
        '#default_value' => variable_get('hdflvplayer_volume', ''),
        '#size' => 20,
        '#description' => t('% Recommended value is 50'),
        '#maxlength' => 30,
    );

    $form['filedset']['Player Settings']['hdflvplayer_skinautohide'] = array(
        '#type' => 'radios',
        '#title' => t('Skin Auto Hide'),
        '#default_value' => variable_get('hdflvplayer_skinautohide', ''),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
    );


    $form['filedset']['Player Settings']['hdflvplayer_fullscreen'] = array(
        '#type' => 'radios',
        '#title' => t('Full Screen'),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
        '#default_value' => variable_get('hdflvplayer_fullscreen', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_zoom'] = array(
        '#type' => 'radios',
        '#title' => t('Zoom'),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
        '#default_value' => variable_get('hdflvplayer_zoom', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_autoplay'] = array(
        '#type' => 'radios',
        '#title' => t('Autoplay'),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
        '#default_value' => variable_get('hdflvplayer_autoplay', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_timer'] = array(
        '#type' => 'radios',
        '#title' => t('Timer'),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
        '#default_value' => variable_get('hdflvplayer_timer', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_share'] = array(
        '#type' => 'radios',
        '#title' => t('Share'),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
        '#default_value' => variable_get('hdflvplayer_share', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_autoplay'] = array(
        '#type' => 'radios',
        '#title' => t('Playlist Autoplay'),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
        '#default_value' => variable_get('hdflvplayer_autoplay', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_playlistopen'] = array(
        '#type' => 'radios',
        '#title' => t('Playlist Open'),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
        '#default_value' => variable_get('hdflvplayer_playlistopen', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_hd'] = array(
        '#type' => 'radios',
        '#title' => t('HD Default'),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
        '#default_value' => variable_get('hdflvplayer_hd', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_vast'] = array(
        '#type' => 'radios',
        '#title' => t('Vast'),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
        '#default_value' => variable_get('hdflvplayer_vast', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_embed'] = array(
        '#type' => 'radios',
        '#title' => t('Embed Code'),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
        '#default_value' => variable_get('hdflvplayer_embed', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_youtube_logo'] = array(
        '#type' => 'radios',
        '#title' => t('Hide Youtube Logo'),
        '#default_value' => variable_get('hdflvplayer_youtube_logo', ''),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
    );

    $form['filedset']['Player Settings']['hdflvplayer_download'] = array(
        '#type' => 'radios',
        '#title' => t('Download'),
        '#default_value' => variable_get('hdflvplayer_download', ''),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
    );
    $form['filedset']['Player Settings']['hdflvplayer_showplaylist'] = array(
        '#type' => 'radios',
        '#title' => t('Showplaylist'),
        '#default_value' => variable_get('hdflvplayer_showplaylist', ''),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
    );

    $form['filedset']['Player Settings']['hdflvplayer_description'] = array(
        '#type' => 'radios',
        '#title' => t('Frontend Description'),
        '#default_value' => variable_get('hdflvplayer_description', ''),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
    );

    $form['filedset']['Player Settings']['hdflvplayer_title'] = array(
        '#type' => 'radios',
        '#title' => t('Frontend Title'),
        '#default_value' => variable_get('hdflvplayer_title', ''),
        '#options' => array('true' => t('Enable'), 'false' => t('Disable')),
    );

    $form['filedset']['Player Settings']['hdflvplayer_skin'] = array(
        '#type' => 'select',
        '#title' => t('Skin Theme'),
        '#options' =>
        array(
            'skin_black.swf' => t('Black'),
            'skin_fancyblack.swf' => t('Facncy Black'),
            'skin_Overlay.swf' => t('Overlay Black'),
            'skin_sleekblack.swf' => t('Sleek Black'),
        ),
        '#default_value' => variable_get('hdflvplayer_skin', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_related'] = array(
        '#type' => 'select',
        '#title' => t('Related Videos'),
        '#options' =>
        array(
            '1' => t('Enable Both'),
            '2' => t('Disable'),
            '3' => t('Within Player'),
            '4' => t('Outside Player'),
        ),
        '#default_value' => variable_get('hdflvplayer_related', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_normal_scale'] = array(
        '#type' => 'select',
        '#title' => t('Normal Screen Scale'),
        '#options' =>
        array(
            '0' => t('Aspect Ratio'),
            '1' => t('Original Size'),
            '2' => t('Fit to Screen'),
        ),
        '#default_value' => variable_get('hdflvplayer_normal_scale', 0),
    );

    $form['filedset']['Player Settings']['hdflvplayer_full_scale'] = array(
        '#type' => 'select',
        '#title' => t('Full Screen'),
        '#options' =>
        array(
            '0' => t('Aspect Ratio'),
            '1' => t('Original Size'),
            '2' => t('Fit to Screen'),
        ),
        '#default_value' => variable_get('hdflvplayer_full_scale', 0),
    );

    /* form submit to system configuration form and store the values in variable table. */

    return system_settings_form($form);
}

/* * ************************************************************** LANGUAGE SETTINGS FORM **************************************************************** */

function hdflvplayer_admin_language(&$form_state) {

    // Add hdflvplayer administration JS/CSS

    drupal_add_css(drupal_get_path('module', 'hdflvplayer') . '/style/hdflvplayerlang.css');

    $form['#attributes'] = array('enctype' => "multipart/form-data");

    $form['filedset'] = array('#type' => 'fieldset',
        '#title' => t('HDFLV Player'),
    );

    /* Language Settings form filelds */
    $form['filedset']['Language'] = array('#type' => 'fieldset',
        '#title' => t('Language'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );

    $form['filedset']['Language']['hdflvplayer_language_name'] = array('#type' => 'textfield',
        '#title' => t('Name'),
        '#default_value' => variable_get('hdflvplayer_language_name', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_play'] = array('#type' => 'textfield',
        '#title' => t('Play'),
        '#default_value' => variable_get('hdflvplayer_language_play', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_pause'] = array('#type' => 'textfield',
        '#title' => t('Pause'),
        '#default_value' => variable_get('hdflvplayer_language_pause', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_hdison'] = array('#type' => 'textfield',
        '#title' => t('HD is on'),
        '#default_value' => variable_get('hdflvplayer_language_hdison', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_hdisoff'] = array('#type' => 'textfield',
        '#title' => t('HD is off'),
        '#default_value' => variable_get('hdflvplayer_language_hdisoff', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_zoom'] = array('#type' => 'textfield',
        '#title' => t('Zoom'),
        '#default_value' => variable_get('hdflvplayer_language_zoom', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_share'] = array('#type' => 'textfield',
        '#title' => t('Share'),
        '#default_value' => variable_get('hdflvplayer_language_share', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_fullscreen'] = array('#type' => 'textfield',
        '#title' => t('Fullscreen'),
        '#default_value' => variable_get('hdflvplayer_language_play', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_relatedvideos'] = array('#type' => 'textfield',
        '#title' => t('Relatedvideos'),
        '#default_value' => variable_get('hdflvplayer_language_relatedvideos', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_sharetheword'] = array('#type' => 'textfield',
        '#title' => t('Sharetheworld'),
        '#default_value' => variable_get('hdflvplayer_language_sharetheword', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_sendanemail'] = array('#type' => 'textfield',
        '#title' => t('Sendanemail'),
        '#default_value' => variable_get('hdflvplayer_language_sendanemail', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_to'] = array('#type' => 'textfield',
        '#title' => t('To'),
        '#default_value' => variable_get('hdflvplayer_language_to', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_from'] = array('#type' => 'textfield',
        '#title' => t('From'),
        '#default_value' => variable_get('hdflvplayer_language_from', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_note'] = array('#type' => 'textfield',
        '#title' => t('Note'),
        '#default_value' => variable_get('hdflvplayer_language_note', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_send'] = array('#type' => 'textfield',
        '#title' => t('Send'),
        '#default_value' => variable_get('hdflvplayer_language_send', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_copylink'] = array('#type' => 'textfield',
        '#title' => t('Copylink'),
        '#default_value' => variable_get('hdflvplayer_language_copylink', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_copyembed'] = array('#type' => 'textfield',
        '#title' => t('Copyembed'),
        '#default_value' => variable_get('hdflvplayer_language_copyembed', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_facebook'] = array('#type' => 'textfield',
        '#title' => t('Facebook'),
        '#default_value' => variable_get('hdflvplayer_language_facebook', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_redit'] = array('#type' => 'textfield',
        '#title' => t('Red it'),
        '#default_value' => variable_get('hdflvplayer_language_redit', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_friendfeed'] = array('#type' => 'textfield',
        '#title' => t('Friend Feed'),
        '#default_value' => variable_get('hdflvplayer_language_friendfeed', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_slashdot'] = array('#type' => 'textfield',
        '#title' => t('Slash Dot'),
        '#default_value' => variable_get('hdflvplayer_language_slashdot', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_delicious'] = array('#type' => 'textfield',
        '#title' => t('Delicious'),
        '#default_value' => variable_get('hdflvplayer_language_delicious', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_myspace'] = array('#type' => 'textfield',
        '#title' => t('Myspace'),
        '#default_value' => variable_get('hdflvplayer_language_myspace', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_wong'] = array('#type' => 'textfield',
        '#title' => t('Wong'),
        '#default_value' => variable_get('hdflvplayer_language_wong', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_digg'] = array('#type' => 'textfield',
        '#title' => t('Digg'),
        '#default_value' => variable_get('hdflvplayer_language_digg', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_blinklist'] = array('#type' => 'textfield',
        '#title' => t('Blinklist'),
        '#default_value' => variable_get('hdflvplayer_language_blinklist', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_bebo'] = array('#type' => 'textfield',
        '#title' => t('Bebo'),
        '#default_value' => variable_get('hdflvplayer_language_bebo', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_fark'] = array('#type' => 'textfield',
        '#title' => t('Fark'),
        '#default_value' => variable_get('hdflvplayer_language_fark', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_tweet'] = array('#type' => 'textfield',
        '#title' => t('Tweet'),
        '#default_value' => variable_get('hdflvplayer_language_tweet', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_furl'] = array('#type' => 'textfield',
        '#title' => t('Furl'),
        '#default_value' => variable_get('hdflvplayer_language_furl', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_btnname'] = array('#type' => 'textfield',
        '#title' => t('Button Name'),
        '#default_value' => variable_get('hdflvplayer_language_btnname', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );
    $form['filedset']['Language']['hdflvplayer_language_download'] = array('#type' => 'textfield',
        '#title' => t('Download'),
        '#default_value' => variable_get('hdflvplayer_language_download', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    $form['filedset']['Language']['hdflvplayer_language_errormessage'] = array('#type' => 'textfield',
        '#title' => t('Error Message'),
        '#default_value' => variable_get('hdflvplayer_language_errormessage', ''),
        '#maxlength' => 50,
        '#size' => 30,
    );

    return system_settings_form($form);
}

/* * ************************************************************** GOOGLE ADDSENSE SETTINGS FORM **************************************************************** */

function hdflvplayer_admin_addsense(&$form_state) {

    // Add hdflvplayer administration JS/CSS

    drupal_add_css(drupal_get_path('module', 'hdflvplayer') . '/style/hdflvplayer-google.css');

    $form['#attributes'] = array('enctype' => "multipart/form-data");

    $form['filedset'] = array('#type' => 'fieldset',
        '#title' => t('HDFLV Player'),
    );

    /* Google Adsense Settings form filelds */
    $form['filedset']['Google Adds'] = array('#type' => 'fieldset',
        '#title' => t('Google Adds'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    $form['filedset']['Google Adds']['hdflvplayer_google_puplished'] = array(
        '#type' => 'radios',
        '#title' => t('Puplished'),
        '#default_value' => variable_get('hdflvplayer_google_puplished', ''),
        '#options' => array('1' => t('Yes'), '2' => t('No')),
    );
    $form['filedset']['Google Adds']['hdflvplayer_google_code'] = array(
        '#type' => 'textarea',
        '#title' => t('Enter the Code'),
        '#default_value' => variable_get('hdflvplayer_google_code', ''),
    );

    $form['filedset']['Google Adds']['hdflvplayer_google_showoption'] = array(
        '#type' => 'radios',
        '#title' => t('Option'),
        '#default_value' => variable_get('hdflvplayer_google_showoption', ''),
        '#options' => array('1' => t('Always Show'), '2' => t('Close After:')),
    );

    $form['filedset']['Google Adds']['hdflvplayer_google_closeadd'] = array('#type' => 'textfield',
        '#description' => t('Sec'),
        '#size' => 8,
        '#default_value' => variable_get('hdflvplayer_google_closeadd', ''),
    );

    $form['filedset']['Google Adds']['hdflvplayer_google_reopenadd'] = array('#type' => 'checkbox',
        '#title' => t('Reopen : After'),
        '#default_value' => variable_get('hdflvplayer_google_reopenadd', ''),
    );

    $form['filedset']['Google Adds']['hdflvplayer_google_ropen'] = array('#type' => 'textfield',
        '#description' => t('Sec'),
        '#size' => 6,
        '#default_value' => variable_get('hdflvplayer_google_ropen', ''),
    );

    return system_settings_form($form);
}
