<?php

// $Id: hdflvplayer_playlist.inc,v 1.0 Created by Vasanth at 2010/01/20 14:19:29 Exp $
/*
 * This file is contain list of playlist details.
 * And we can edit and delete playlist details here.
 */
/* * ****************************************************** HDFLV Playlist Details in list ************************************************************************ */
/*
 * Retrive playlist details from hdflvplayer_playlist.
 */
function hdflvplayer_playlist_form() {

    /* Assign variable form in array for retrun the form element values. */

    $form = array();

    /* Retrive the values from database */

    $result = db_query('SELECT * FROM {hdflvplayer_playlist} where 1');

    while ($rows = db_fetch_object($result)) {
        if ($rows->published == '1') {
            $published = 'Yes';
        } else {
            $published = 'No';
        }
        $output .= '<tr><td>' . $rows->playid . '</td><td>' . $rows->name . '</td><td>' . $published . '</td><td><a href="editplaylist/' . $rows->playid . '">Edit | </a><a href="deleteplaylist/' . $rows->playid . '">Delete</a></td></tr>';
    }

    $form['#prefix'] = '<div id="play_list"><table class="widefat" cellspacing="0">
           <table class="widefat" cellspacing="0">
            <thead>
                <tr>
                    <th id="id" scope="col">ID </th>                                     
                     <th id="path"  scope="col">Playlist Name</th>
                     <th id="path"  scope="col">Published</th>
                    <th id="path"   scope="col"><a href="addplaylist/">Add PlayList</a></th>
                </tr>
            </thead><tbody>' . $output . '</tbody></table></div>';

    return $form;
}
