<?php
/**
 * @file
 * Theme and preprocess functions for the Video.js module.
 */

/**
 * Preprocess function for videojs.tpl.php when using a playlist.
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

  // Add the defaults to $vars['attributes'] and merge with $vars.
  $options = videojs_utility::getDisplaySettings($vars['attributes']);
  $vars = array_merge($vars, $options);
  $vars['items'] = array();
  $vars['tracks'] = array();
  $vars['poster'] = NULL;

  foreach ($items as $item) {
    if (empty($item['filemime'])) {
      continue;
    }

    if (!isset($codecs[$item['filemime']])) {
      // check for image file and add in it as poster
      if (strncmp($item['filemime'], 'image/', 6) === 0) {
        $vars['poster'] = $item['uri'];
      }

      // Filter out tracks.
      if (strncmp($item['filemime'], 'text/vtt', 8) === 0) {
        $item = $item + array(
          'default' => FALSE,
          'kind' => 'subtitles',
          'charset' => 'utf-8',
          'description' => '',
          'langcode' => '',
        );

        // Try to find the language for subtitles.
        if (empty($item['langcode'])) {
          $language = videojs_utility::resolveLanguage($item['description']);
          if ($language !== NULL) {
            $item['langcode'] = $language[0];
            if (empty($item['description'])) {
              $item['description'] = $language[1];
            }
          }
        }

        $vars['tracks'][] = $item;
      }

      // Skip unplayable items.
      continue;
    }

    $item['videotype'] = $codecs[$item['filemime']];

    $vars['items'][] = $item;
  }

  // Turn the poster image URI into a URL
  if (!empty($vars['poster'])) {
    if (empty($vars['posterimage_style'])) {
      $vars['poster'] = file_create_url($vars['poster']);
    }
    else {
      $vars['poster'] = image_style_url($vars['posterimage_style'], $vars['poster']);
    }
  }
}