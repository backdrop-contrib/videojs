<?php
/**
 * @file
 * Administrative pages for the Video.js module.
 */

/**
 * Menu callback; Provides the Video.js settings form.
 */
function videojs_settings_form() {
  $form = array();

  $form['location'] = array(
    '#type' => 'fieldset',
    '#title' => t('Video.js location'),
    '#collapsible' => FALSE,
  );

  $locations = array(
    'cdn' => t('Video.js Content Delivery Network (CDN)'),
    'path' => t('Specified path'),
  );

  if (module_exists('libraries')) {
    $locations['libraries'] = t('Libraries API');
  }

  $form['location']['videojs_location'] = array(
    '#type' => 'select',
    '#title' => t('Video.js location'),
    '#options' => $locations,
    '#default_value' => variable_get('videojs_location', 'cdn'),
  );

  $form['location']['videojs_directory'] = array(
    '#type' => 'textfield',
    '#title' => t('Video.js file directory'),
    '#default_value' => variable_get('videojs_directory', 'sites/all/libraries/video-js'),
    '#description' => t('Specify the path that contains the Video.js library. The video.js file should be in the root of this directory.') . '<br/>' . t('This path can be either local (sites/all/libraries/video-js) or remote (http://yourcdn.com/video-js).'),
    '#states' => array(
      'visible' => array(
        ':input[name="videojs_location"]' => array('value' => 'path'),
      ),
    ),
  );

  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Player defaults'),
    '#collapsible' => FALSE,
  );

  $form['options']['videojs_autoplay'] = array(
    '#type' => 'checkbox',
    '#title' => t('Auto-play files on page load'),
    '#description' => t('Use caution when combining this option with multiple players on the same page.'),
    '#default_value' => variable_get('videojs_autoplay', FALSE),
  );

  $form['options']['videojs_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Player width'),
    '#default_value' => variable_get('videojs_width', 640),
    '#element_validate' => array('_element_validate_integer_positive'),
  );

  $form['options']['videojs_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Player height'),
    '#default_value' => variable_get('videojs_height', 360),
    '#element_validate' => array('_element_validate_integer_positive'),
  );

  $form['#validate'][] = 'videojs_settings_form_validate';
  $form['#submit'][] = 'videojs_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Validation function to validate the videojs_settings_form() form.
 */
function videojs_settings_form_validate($form, &$form_state) {
  $form_state['values']['videojs_directory'] = rtrim($form_state['values']['videojs_directory'], '/');
  $location = $form_state['values']['videojs_location'];

  switch ($location) {
    case 'path':
      $form_state['videojs_version'] = videojs_get_version($form_state['values']['videojs_directory']);
      $form_state['videojs_directory'] = $form_state['values']['videojs_directory'];
      if (!$form_state['videojs_version']) {
        form_error($form['location']['videojs_directory'], t('The directory specified does not seem to contain the Video.js library. Check to make sure that the video.js file is located within this directory.'));
      }
      break;

    case 'libraries':
      $form_state['videojs_directory'] = libraries_get_path('video-js');
      $form_state['videojs_version'] = videojs_get_version($form_state['videojs_directory']);
      if (empty($form_state['videojs_directory']) || !$form_state['videojs_version']) {
        form_error($form['location']['videojs_location'], t('The Libraries API could not find the location of Video.js. Please put Video.js at the right location or select another location type.'));
      }
      break;

    case 'cdn':
    default:
      $form_state['videojs_version'] = '4';
      break;
  }

  if (!empty($form_state['videojs_version']) && version_compare($form_state['videojs_version'], '4', '<')) {
    form_error($form['location']['videojs_location'], t('Version @version of Video.js was found, but this version is not supported. Use version 4 of the Video.js player or another version of the Video.js module.', array('@version' => $form_state['videojs_version'])));
  }
}

/**
 * Submit handler for the videojs_settings_form() form.
 */
function videojs_settings_form_submit($form, &$form_state) {
  // Fix the variable types and make sure empty values are not saved.
  variable_del('videojs_autoplay');
  variable_del('videojs_width');
  variable_del('videojs_height');

  $form_state['values']['videojs_autoplay'] = $form_state['values']['videojs_autoplay'] == '1';
  $form_state['values']['videojs_width'] = intval($form_state['values']['videojs_width']);
  $form_state['values']['videojs_height'] = intval($form_state['values']['videojs_height']);

  if (!$form_state['values']['videojs_autoplay']) {
    unset($form_state['values']['videojs_autoplay']);
  }
  if ($form_state['values']['videojs_width'] == 0) {
    unset($form_state['values']['videojs_width']);
  }
  if ($form_state['values']['videojs_height'] == 0) {
    unset($form_state['values']['videojs_height']);
  }

  if ($form_state['values']['videojs_location'] != 'cdn') {
    drupal_set_message(t('The Video.js library (version @version) was successfully found at %directory.', array('@version' => $form_state['videojs_version'], '%directory' => $form_state['videojs_directory'])));
  }
}