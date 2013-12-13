// $Id: linkedin.js,v 1.1.2.1 2010/05/13 12:29:36 bellesmanieres Exp $

/*
 * @file : hide the textfield on user posting form until enabled by checkbox.
 */
Drupal.behaviors.linkedin = function(context) {

  if (!$("#linkedin-status-posting").attr("checked")) {
    $("#linkedin-status-textfield-wrapper").hide();
  }
  $("#linkedin-status-posting").bind("click", function() {
    if ($("#linkedin-status-posting").attr("checked")) {
      $("#linkedin-status-textfield-wrapper").show();      
    }
    else {
      $("#linkedin-status-textfield-wrapper").hide();
    }
  });
}
