<?php
// $Id: linkedin.pages.inc,v 1.1.2.5 2010/05/13 12:29:36 bellesmanieres Exp $

/*
 * @file : Pages callbacks and form builder functions for linkedin module
*/

/*
 * Callback for admin settings at admin/settings/linkedin
*/
function linkedin_admin() {
//LinkedIn API credentials
  global $base_url;
  $form['consumer'] = array(
          '#description'    => t('You will get theses values by requesting an API key at https://www.linkedin.com/secure/developer. <br /><em>Notice that the "integration url" you specify at Linkedin must match the base url (@url)</em>', array('@url' => $base_url)),
          '#title'          => t('Consumer information'),
          '#type'           => 'fieldset',
  );
  $form['consumer']['linkedin_consumer_key'] = array(
          '#default_value'  => variable_get('linkedin_consumer_key', ''),
          '#title'          => t('Consumer key'),
          '#type'           => 'textfield',
  );
  $form['consumer']['linkedin_consumer_secret'] = array(
          '#default_value'  => variable_get('linkedin_consumer_secret', ''),
          '#title'          => t('Consumer secret'),
          '#type'           => 'textfield',
  );

//LinkedIn status update settings
  $form['posting'] = array(
          '#description'    => t('Enable users to update their LinkedIn user status when performing following actions.'),
          '#title'          => t('Status update'),
          '#type'           => 'fieldset',
          '#collapsible'           => TRUE,
          '#collapsed'           => TRUE,
  );
  $form['posting']['node_types'] = array(
          '#description'    => t('Let users update their status when creating/editing nodes of these types.'),
          '#title'          => t('Node types'),
          '#type'           => 'fieldset',
  );
  $types = node_get_types('names');
  foreach($types as $type) {
    $type = strtolower($type);
    $form['posting']['node_types']['linkedin_enabled_'. $type] = array(
            '#type' => 'checkbox',
            '#prefix' =>'<div class="linkedin-checkbox-toggle">',
            '#suffix' =>'</div>',
            '#title' => $type,
            '#default_value' => variable_get('linkedin_enabled_'. $type, '0'),
    );
    $form['posting']['node_types']['linkedin_default_format_'. $type] = array(
            '#type' => 'textfield',
            '#prefix' =>'<div class="linkedin-hidden">',
            '#suffix' =>'</div>',
            '#title' => t('Default format string'),
            '#maxlength' => 140,
            '#description' => t('Text that will be posted to Linked In. You can use !url, !title, !user, and !site as replacement text.'),
            '#default_value' => variable_get('linkedin_default_format_'. $type, 'Posted "!title" on !site : !url'),
    );
  }
  if(module_exists('signup')) {
    $form['posting']['event_signup'] = array(
            '#description'    => t('Let users update their status when signing up to events.'),
            '#title'          => t('Users signup'),
            '#type'           => 'fieldset',
    );
    $form['posting']['event_signup']['linkedin_enabled_event_signup'] = array(
            '#type' => 'checkbox',
            '#title' => 'Enable',
            '#default_value' => variable_get('linkedin_enabled_event_signup', '0'),
    );
    $form['posting']['event_signup']['linkedin_default_format_event_signup'] = array(
            '#type' => 'textfield',
            '#title' => t('Default format string'),
            '#maxlength' => 140,
            '#description' => t('Text that will be posted to Linked In. You can use !url, !title, !user, and !site as replacement text.'),
            '#default_value' => variable_get('linkedin_default_format_event_signup', 'Posted "!title" on !site : !url'),
    );
  };

//Enable status update on comments
  if(module_exists('comment')) {
    $form['posting']['comment'] = array(
            '#description'    => t('Let users update their status when adding comments to a Linkedin enabled node.'),
            '#title'          => t('Comments'),
            '#type'           => 'fieldset',
    );
    $form['posting']['comment']['linkedin_enabled_comment'] = array(
            '#type' => 'checkbox',
            '#title' => 'Enable',
            '#default_value' => variable_get('linkedin_enabled_event_signup', '0'),
    );
    $form['posting']['comment']['linkedin_default_format_comment'] = array(
            '#type' => 'textfield',
            '#title' => t('Default format string'),
            '#maxlength' => 140,
            '#description' => t('Text that will be posted to Linked In. You can use !url, !title, !user, and !site as replacement text.'),
            '#default_value' => variable_get('linkedin_default_format_comment', 'Commented on  "!title" on !site : !url'),
    );
  };

//User profile settings
  $form['profile'] = array(
          '#description'    => t('Enable users to display information from their LinkedIn page on their local profile.'),
          '#title'          => t('User profile'),
          '#type'           => 'fieldset',
          '#collapsible'           => TRUE,
          '#collapsed'           => TRUE,
  );
  $form['profile']['linkedin_profile_enabled'] = array(
          '#type' => 'select',
          '#title' => 'Profile display',
          '#options' => array(
                  '0' => t('Disabled'),
                  '1' => t('Tab'),
                  '2' => t('Profile item'),
                  '3' => t('Block'),
                  '4' => t('Hidden'),
          ),
          '#default_value' => variable_get('linkedin_profile_enabled', '0'),
  );
  $form['profile']['linkedin_profile_weight'] = array (
          '#type' => 'textfield',
          '#title' => t('Profile item weight'),
          '#maxlength' => 4,
          '#size' => 2,
          '#description' => t('Changing this value will make the "Profile item" display move below or after other elements on the user page. E.g. setting this to 100 will make it the very last element.'),
          '#default_value' => variable_get('linkedin_profile_weight', 2),
  );

  //$form['#submit'][] = 'linkedin_admin_submit';
  return system_settings_form($form);
}


//function linkedin_admin_submit(&$form_state) {
//  drupal_flush_all_caches();
//  drupal_set_message('cah');
//}
/*
 * Callback for linkedin related user settings at user/%/edit/linkedin
*/
function linkedin_user_settings($account) {
  $output = '';
  $check = linkedin_get_profile_fields($account->uid, array('id'));
  if(!isset($check['person']['id'])) {
    $output .= '<p>You must first authorize LinkedIn integration to use related features.</p>';
    $output .= drupal_get_form('linkedin_user_enable_form', $account->uid);
  } else {
    $output .= drupal_get_form('linkedin_user_settings_form', $account);
  }
  return $output;
}

/*
 * Take users to linkedin auth page
*/
function linkedin_user_enable_form($form_state, $uid) {
  $form = array();
  $form['#user'] = $uid;
  $form['#action'] = url('linkedin/token/'. $uid);
  $form['submit'] = array(
          '#type' => 'submit',
          '#value' => t('Go LinkedIn'),
          '#suffix' => '<p class="description">'. t('You will be taken to LinkedIn website in order to complete the process.') .'</p>',
  );
  return $form;
}

/*
 * form for individual user settings
*/
function linkedin_user_settings_form($form_state, $account) {
  $form = array();
  $form['#account'] = $account;
  if(variable_get('linkedin_profile_enabled', '0') >= '1' && user_access('display LinkedIn profile')) {
    $form['linkedin_profile_enabled'] =array(
            '#type'  => 'checkbox',
            '#default_value' => isset($account->linkedin_profile_enabled) ? $account->linkedin_profile_enabled : '0',
            '#title' => t('Display an abstract of your LinkedIn page on your current profile page'),
    );
  }

  if(user_access('update LinkedIn status')) {
//check if linkedin status update is enabled for at least one content type
    $types = node_get_types('names');
    array_push($types, 'event_signup');
    foreach($types as $type) {
      $type = strtolower($type);
      if(variable_get('linkedin_enabled_'. $type, '0' == '1')) {
//if true add related option
        $form['linkedin_status_enabled_by_default'] =array(
                '#type'  => 'checkbox',
                '#default_value' => isset($account->linkedin_status_enabled_by_default) ? $account->linkedin_status_enabled_by_default : '0',
                '#title' => t('By default, on actions such as posting content, update your LinkedIn status'),
                '#description' => t('(You can always bypass this setting individually)'),
        );
        break;
      }
    }
  }

  $form['submit'] = array(
          '#type' => 'submit',
          '#value' => 'Save',
  );
  $form['linkedin']['reset'] = array(
          '#type' => 'submit',
          '#description' => t('Click here to unlink your LinkedIn account.'),
          '#value' => t('Unlink'),
  );

  return $form;
}

function linkedin_user_settings_form_submit($form, &$form_state) {
// basic security checks, as we didn't pass throught validate (checkboxes only);
  $op = $form_state['values']['op'];
  global $user;
  if ($form['#account']->uid == $user->uid || user_access('administer users')) {
    if ($op == $form['linkedin']['reset']['#value']) {
      user_save($form['#account'], array('linkedin_profile_enabled' => NULL, 'linkedin_status_enabled_by_default' => NULL,), 'linkedin');
      db_query("DELETE FROM {linkedin_token} WHERE uid = %d", $form['#account']->uid);
      drupal_set_message(t('LinkedIn preferences have been reset'));
    } else {
      user_save($form['#account'], array('linkedin_profile_enabled' => $form_state['values']['linkedin_profile_enabled'], 'linkedin_status_enabled_by_default' => $form_state['values']['linkedin_status_enabled_by_default'],), 'linkedin');
      drupal_set_message(t('LinkedIn preferences have been saved'));
    }
  }
}

/*
 * Form that will appear on places where users can update their linkedin status (node edit, signup, ...)
*/
function linkedin_user_status_update_form($form_state, $user, $node) {
// set up the state of the checkbox in the form
  if (isset($user->linkedin_status_enabled_by_default) && !isset($node->nid)) {
    $checked = 1;
  }
  else {
    $checked = 0;
  }

//prepare the form base checkbox
  $form['linkedin_status'] = array(
          '#type' => 'fieldset',
          '#title' => t('Post to LinkedIn'),
          '#tree' => TRUE,
  );
  $form['linkedin_status']['posting'] = array(
          '#type' => 'checkbox',
          '#id' => 'linkedin-status-posting',
          '#default_value' => $checked,
  );
  $form['linkedin_status']['posting']['#title'] = t('Announce on LinkedIn');

//check if user can post to LinkedIn. No need to load all the following if the form is to be disabled anyway
  $check = linkedin_get_profile_fields($user->uid, array('id'));
  if(!isset($check['person']['id'])) {//disabling form for users who have not yet authorised our site and link them to the right place
    $form['linkedin_status']['posting']['#disabled'] = TRUE;
    $form['linkedin_status']['posting']['#prefix'] = '<p>'. t('You must first authorize this feature in your user profile : !url', array('!url' => l($user->name, 'user/'. $user->uid .'/edit/linkedin'))) .'</p>';
  }
  else { //user can post
    $form['#title'] = $node->title;
    $form['#url'] = url('node/'. $node->nid, array('absolute' => TRUE));
    $form['#user'] = $user->name;
    $form['#site'] = variable_get('site_name', $base_url);

//add textfield is user has perm.
    if(user_access('use custom status text')) {
// two lines of js for hiding the texfield if checkbox is unchecked.
      drupal_add_js(drupal_get_path('module', 'linkedin') .'/linkedin.js', 'module');
      $form['linkedin_status']['status'] = array(
              '#type' => 'textfield',
              '#default_value' => variable_get('linkedin_default_format_'. $node->type, ''),
              '#description' => t('This text will be set as your current status on linkedin. You can use !title, !url, !user and !site as replacement text.'),
              '#id' => 'linkedin-status-textfield',
      );
    } else {
      $form['linkedin_status']['status'] = array(
              '#type' => 'hidden',
              '#value' => variable_get('linkedin_default_format_'. $node->type, ''),
      );
    }
  }
  return $form;
}

/*
 * Submit for user posting their status
*/
function linkedin_user_status_update_form_submit($form, &$form_state) {

  if ($form_state['values']['linkedin_status']['posting'] == '1' && !empty($form_state['values']['linkedin_status']['status']) && user_access('update LinkedIn status')) {

    if($form['linkedin']) {//for forms on node edit page
      $prefix = $form['linkedin'] ;
    } elseif($form['collapse']['signup_user_form']['linkedin']) { //for forms on event signup
      $prefix = $form['collapse']['signup_user_form']['linkedin'];
    } else { //shouldn't occur, something is wrong !!!!
      drupal_set_message('Linkedin module has a serious problem! Please file an issue at http://drupal.org/project/linkedin');
      return;
    }
    if(!empty($form_state['values']['nid'])) {
      $placeholders = array(
              '!title' => $prefix['#title'],
              '!url' => $prefix['#url'],
              '!user' => $prefix['#user'],
              '!site' => $prefix['#site'],
      );

      global $user;

      $status = strtr($form_state['values']['linkedin_status']['status'], $placeholders);
      linkedin_put_profile_field($user->uid, 'current-status', $status);
      drupal_set_message(t('Posted to LinkedIn'));
    }
  }
}

/*
 * Page callback for user profile linkedin tab
*/
function linkedin_profile_display($account) {
  $profile = linkedin_get_profile_fields($account->uid, array(
          'picture-url',
          'first-name',
          'last-name',
          'headline',
          'location',
          'industry',
          'summary',
          'specialties',
          'public-profile-url',
          'current-status-timestamp',
          'current-status',
          ), TRUE);
  if(!$profile == 'refused');
  return theme('linkedin_profile', $profile);
}
