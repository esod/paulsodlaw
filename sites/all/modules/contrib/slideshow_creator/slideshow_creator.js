/**
 * @author: Bruno Massa http://drupal.org/user/67164
 * @file slideshow_creator.js
 * The main Javacript for this module
 */
/*global Drupal, $ */

/**
 * Initialize the module's JS functions
 */
Drupal.behaviors.ssc = function(context) {
  if (typeof(window['ssc_settings']) != 'undefined' ) {
    for (var ss in ssc_settings) {
      if (ssc_settings.hasOwnProperty(ss)) {
	ssc_settings[ss].before = Drupal.ssc_before;
	$("#ssc-content-" + ss).cycle(ssc_settings[ss]);
      }
    }
  }
};

Drupal.ssc_before = function() {
  var sscid = this.id.replace(/ssc-slide-/, "").replace(/-.*/, "");
  var slide = parseInt(this.id.replace(/ssc-slide-.*-/, ""), 10) + 1;
  $("#ssc-current-" + sscid).html(slide);
};
