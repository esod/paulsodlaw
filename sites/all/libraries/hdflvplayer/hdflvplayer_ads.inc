<?php

// $Id: hdflvplayer_playlist.inc,v 1.0 Created by Vasanth at 2010/01/20 14:19:29 Exp $
/*
 * This file is contain list of playlist details.
 * And we can edit and delete details here.
 */
/* * ****************************************************** HDFLV Playlist Details in list ************************************************************************ */
/*
 * Retrive playlist details from hdflvplayer_playlist.
 */
function hdflvplayer_ads_form() {

    /*Assign variable form in array for retrun the form element values.*/

    $form = array();

    /*Retrive the values from database*/
    
    $result = db_query('SELECT * FROM {hdflvplayerads} where 1');

    while ($rows = db_fetch_object($result)) {
        if ($rows->published == '1') {
            $published = 'Yes';
        } else {
            $published = 'No';
        }
        $output .= '<tr><td>' . $rows->id . '</td><td>' . $rows->adsname . '</td><td>' . $published . '</td><td>' . $rows->clickurl . '</td><td>' . $rows->impressionurl . '</td><td><a href="editads/' . $rows->id . '">Edit | </a><a href="deleteads/' . $rows->id . '">Delete</a></td></tr>';
    }

    $form['#prefix'] = '<div id="ads_list"><table class="widefat" cellspacing="0">
           <table class="widefat" cellspacing="0">
            <thead>
                <tr>
                    <th id="id" scope="col">ID </th>                                     
                     <th id="path"  scope="col">Ads name</th> 
                     <th id="path"  scope="col">Published</th>
                     <th id="path"  scope="col">Click Hits</th>
                     <th id="path"  scope="col">Impression Hits</th>
                    <th id="path"   scope="col"><a href="addads/">Add Ads</a></th>
                </tr>
            </thead><tbody>' . $output . '</tbody></table></div>';

    return $form;
}
