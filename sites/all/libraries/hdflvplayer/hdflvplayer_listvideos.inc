<?php

// $Id: hdflvplayer_profiles.inc,v 1.0 Created by Vasanth at 2010/01/19 12:19:29 Exp $
/*
 * This file is contain list of videos details.
 * And we can edit and delete video details here.
 */

/* * ****************************************************** HDFLV Videos Details in list ************************************************************************ */
/*
 * Retrive playlist details from hdflvplayerupload.
 */

function hdflvplayer_listvideos_form() {

    $result = db_query('SELECT * FROM {hdflvplayerupload}');

    /* Assign variable form in array for retrun the form element values. */

    $form = array();

    /* Retrive the values from database */

    while ($tables = db_fetch_object($result)) {

        $results = db_query('SELECT name FROM {hdflvplayer_playlist} where playid="' . $tables->playlistid . '"');

        $result1 = db_fetch_array($results);

        /* Retrive the playlist values from database */

        if ($result1['name'] == '') {
            $result1['name'] = "None";
        }

        $output .= '<tr><td>' . $tables->id . '</td><td>' . $tables->title . '</td><td>' . $result1['name'] . '</td><td>' . $tables->ordering . '</td><td><a href="editvideo/' . $tables->id . '">Edit | </a><a href="delete/' . $tables->id . '">Delete</a></td></tr>';
    }

    $form['#prefix'] = '<div id="video_list"><table class="widefat" cellspacing="0">
           <table class="widefat" cellspacing="0">
            <thead>
                <tr>
                    <th id="id" scope="col">ID </th>
                    <th id="title" scope="col">Title </th>                   
                     <th id="path"  scope="col">Playlist Name</th>
                    <th id="path"   scope="col">Ordering</th>
                    <th id="path"   scope="col"><a href="addvideo/">Add Video </a></th>
                </tr>
            </thead><tbody>' . $output . '</tbody></table></div>';

    return $form;
}
