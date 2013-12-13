<?php
/**
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 * An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
//function phptemplate_breadcrumb($breadcrumb) {
//  if (!empty($breadcrumb)) {
//    return '<span class="breadcrumb">'. implode(' * ', $breadcrumb) .'</span>';
//  }
// }

/**
 * Implementation of $themeenginename_preprocess_$hook().
 * Variables we set here will be available to the breadcrumb template file.
 */
function phptemplate_preprocess_breadcrumb(&$variables) {
  $variables['breadcrumb_delimiter'] = ' || ';
}
