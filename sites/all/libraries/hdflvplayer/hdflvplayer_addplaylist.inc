<?php

// $Id: hdflvplayer_addplaylist.inc,v 1.0 Created by Vasanth at 2010/01/20 15:22:54 Exp $
/*
 * This file is used to add the playlist.
 */
/* * ****************************************************** HDFLV Playlist Add Form ************************************************************************ */
/*
 * Add playlist from elements.
 */
function hdflvplayer_addplaylist_form(&$form_state, $pid, $id=null) {

    /* Add css. */

    drupal_add_css(drupal_get_path('module', 'hdflvplayer') . '/style/hdflvplayerplaylist.css');

    $form = array();

    /* set the form elements for addplaylist. */

    $form['name'] = array(
        '#title' => t('Playlist Name'),
        '#type' => 'textfield',
        '#size' => 30,
        '#required' => TRUE,
    );

    $form['published'] = array(
        '#type' => 'radios',
        '#title' => t('Published'),
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
 * Add playlist from elements submit function.
 */

function hdflvplayer_addplaylist_form_submit($form, &$form_state) {

    /* get the values from post. */

    $name = $form_state['clicked_button']['#post']['name'];

    $published = $form_state['clicked_button']['#post']['published'];

    /* database query for insert the values into database. */

    db_query("INSERT INTO {hdflvplayer_playlist}  (`name`,`published`) VALUES ( '$name','$published')");

    /* Set message after insert the values into database. */

    drupal_set_message(t('Playlist Inserted into Database'));

    /* Set Redirect path after insert the values into database. */

    $form_state['redirect'] = 'admin/hdflvplayer/videos/playlist';
}

