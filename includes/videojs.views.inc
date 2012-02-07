<?php
/**
 * @file
 * Views module hooks for the Video.js module.
 */

/**
 * Implements hook_views_plugins().
 */
function videojs_views_plugins() {
  $path = drupal_get_path('module', 'videojs');

  return array(
    'style' => array(
      'videojs' => array(
        'title' => t('Video.js : HTML5 Video Player'),
        'help' => t('Display video files from different nodes as a Video.js HTML5 video.'),
        'handler' => 'videojs_style_plugin',
        'path' => $path . '/includes',
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
      ),
    ),
  );
}
