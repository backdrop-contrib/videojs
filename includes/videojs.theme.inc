<?php
/**
 * @file
 * Theme and preprocess functions for the Video.js module.
 */

/**
 * Preprocess function for videojs.tpl.php.
 */
function videojs_preprocess_videojs(&$vars) {
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
    'audio/mpeg' => 'audio/mpeg',
    'audio/ogg' => 'audio/ogg',
    'application/vnd.apple.mpegurl' => 'application/vnd.apple.mpegurl', // .m3u8
  );

  $settings = videojs_utility::getDisplaySettings($vars['video_attributes']);
  $vars['attributes']['data-setup'] = '{}';

  // Set the element ID
  $vars['attributes']['id'] = $vars['player_id'] . '-video';

  // Set the video's width and height
  $vars['attributes']['width'] = $settings['width'];
  $vars['attributes']['height'] = $settings['height'];

  // Set preload.
  $vars['attributes']['preload'] = $settings['preload'];

  // Default classes.
  $vars['attributes']['class'] = array(
    'video-js',
    'vjs-default-skin',
  );

  // Define empty poster attribute.
  $vars['attributes']['poster'] = NULL;

  // Display or hide the controls.
  if (!$settings['hidecontrols']) {
    $vars['attributes']['controls'] = 'controls';
  }

  // Display or hide the controls.
  if ($settings['loop']) {
    $vars['attributes']['loop'] = 'loop';
  }

  // Allow autoplay
  if ($settings['autoplay']) {
    $vars['attributes']['autoplay'] = 'autoplay';
  }

  $vars['items'] = array();
  $vars['tracks'] = array();

  foreach ($items as $item) {
    
    // Add src variables.
    if (!empty($item['uri'])) {
      $src = file_create_url($item['uri']);
      $item['src'] = array('raw' => $src, 'safe' => check_plain($src));
    }
    
    if (empty($item['filemime'])) {
      continue;
    }

    if (!isset($codecs[$item['filemime']])) {
      // check for image file and add in it as poster
      if (strncmp($item['filemime'], 'image/', 6) === 0) {
        $settings['poster'] = $item['uri'];
      }

      // Filter out tracks.
      if (strncmp($item['filemime'], 'text/vtt', 8) === 0) {
        // Add raw/safe for videotype var.
        $item['filemime'] = array('raw' => $item['filemime'], 'safe' => check_plain($item['filemime']));
        $vars['tracks'][] = $item + array(
          'default' => FALSE,
          'kind' => 'subtitles',
          'charset' => 'utf-8',
          'label' => '',
          'langcode' => '',
        );
      }

      // Skip unplayable items.
      continue;
    }

    // Add raw/safe for videotype var.
    $item['videotype'] = array('raw' => $codecs[$item['filemime']], 'safe' => check_plain($codecs[$item['filemime']]));

    $vars['items'][] = $item;
  }

  // Turn the poster image URI into a URL, if it isn't an URL already.
  if (!empty($settings['poster']) && strncmp($settings['poster'], 'http://', 7) !== 0  && strncmp($settings['poster'], 'https://', 8) !== 0) {
    if (empty($vars['posterimage_style'])) {
      $vars['attributes']['poster'] = file_create_url($settings['poster']);
    }
    else {
      $vars['attributes']['poster'] = image_style_url($vars['posterimage_style'], $settings['poster']);
    }
  }
}

/**
 * Preprocess function for videojs-media-wysiwyg-preview.tpl.php.
 */
function videojs_preprocess_videojs_media_wysiwyg_preview(&$vars) {
  videojs_preprocess_videojs($vars);

  // If the video has no poster image, borrow one from the media module.
  // This theme function should only be used by the media module, so assume
  // it is loaded.
  if (empty($vars['poster'])) {
    $poster = backdrop_get_path('module', 'media') . '/images/icons/default/video-x-generic.png';
    $raw = file_create_url($poster);
    $vars['poster'] = array('raw' => $raw, 'safe' => check_plain($raw));
  }
}
