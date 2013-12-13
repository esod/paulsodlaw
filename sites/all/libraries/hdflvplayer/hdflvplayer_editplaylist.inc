<?php

// $Id: hdflvplayer_editplaylist.inc,v 1.0 Created by Vasanth at 2010/01/20 15:41:29 Exp $
/*
 * This file is used to edit the playlist details.
 */
/* * ****************************************************** HDFLV Playlist Edit Form ************************************************************************ */
/*
 * Edit playlist from elements.
 */
function hdflvplayer_playlist_edit_form(&$form_state, $pid, $id=null) {

    /* Add css an js */

    drupal_add_css(drupal_get_path('module', 'hdflvplayer') . '/style/hdflvplayeradd.css');

    if ($pid != '') {
        $result = db_fetch_array(db_query('SELECT * FROM {hdflvplayer_playlist} WHERE playid = "%s"', $pid));
    }

    $form['hiddenfile'] = array(
        '#type' => 'hidden',
        '#name' => 'id',
        '#id' => 'idvalue',
        '#value' => $pid,
    );

    $form['name'] = array(
        '#title' => t('PlayList Name'),
        '#type' => 'textfield',
        '#name' => 'name',
        '#id' => 'name',
        '#size' => 30,
        '#value' => $result['name'],
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

function hdflvplayer_playlist_edit_form_submit($form, &$form_state) {

    /* get the values from post. */

    $published = $form_state['clicked_button']['#post']['published'];

    $name = trim($form_state['clicked_button']['#post']['name']);

    $id = $form_state['clicked_button']['#post']['id'];

    /* database query for update the values into database. */

    db_query("update {hdflvplayer_playlist} SET published = '" . $published . "', name = '" . $name . "' where playid='" . $id . "'");

    /* Set message after update the values into database. */

    drupal_set_message(t('Playlist Updated Successfully'));

    /* Set Redirect path after update the values into database. */

    $form_state['redirect'] = 'admin/hdflvplayer/videos/playlist';
}
