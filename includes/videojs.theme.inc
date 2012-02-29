<?php
/**
 * @file
 * Theme and preprocess functions for the Video.js module.
 */

/**
 * Preprocess function for videojs.tpl.php when using a playlist.
 */
function template_preprocess_videojs(&$vars) {
  videojs_add();

  $items = $vars['items'];
  $codecs = array(
    'video/mp4' => 'video/mp4',
    'video/x-m4v' => 'video/mp4',
    'video/webm' => 'video/webm',
    'application/octet-stream' => 'video/webm',
    'video/ogg' => 'video/ogg',
    'application/ogg' => 'video/ogg',
    'video/quicktime' => 'video/mp4',
    'video/flv' => 'video/flv',
    'video/x-flv' => 'video/flv',
  );

  $vars['width'] = !empty($vars['attributes']['width']) ? $vars['attributes']['width'] : variable_get('videojs_width', 640);
  $vars['height'] = !empty($vars['attributes']['height']) ? $vars['attributes']['height'] : variable_get('videojs_height', 264);
  $vars['autoplay'] = !!variable_get('videojs_autoplay', FALSE);
  $vars['items'] = array();
  $vars['poster'] = NULL;

  foreach ($items as $item) {
    if (!isset($codecs[$item['filemime']])) {
      // check for image file and add in it as poster
      $image = file_validate_is_image((object) $item);
      if (empty($image)) {
        $vars['poster'] = file_create_url($item['uri']);
      }

      // Skip unplayable items.
      continue;
    }

    $item['videotype'] = $codecs[$item['filemime']];

    $vars['items'][] = $item;
  }
}

/**
 * Preprocess function for videojs.tpl.php when displaying a view as a playlist.
 */
function template_preprocess_videojs_view(&$vars) {
  videojs_add();
  $vars['player_id'] = 'videojs-view-' . str_replace('_', '-', $vars['view']->name);
}