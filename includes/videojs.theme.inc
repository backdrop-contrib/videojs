<?php

/**
 * Theme and preprocess functions for the videojs module.
 */

/**
 * Preprocess function for videojs.tpl.php when using a playlist.
 */
function template_preprocess_videojs(&$vars) {
  $count = count($vars['items']);
  $number = 0;
  foreach ($vars['items'] as $delta => $item) {
    $vars['items'][$delta]['url'] = file_create_url($item['uri']);
    $vars['items'][$delta]['label'] = $item['description'] ? $item['description'] : $item['filename'];
    $vars['items'][$delta]['class'] = implode(' ', $classes);
  }
}

/**
 * Preprocess function for videojs.tpl.php when displaying a view as a playlist.
 */
function template_preprocess_videojs_view(&$vars) {
  videojs_add();
  $vars['player_id'] = 'videojs-view-' . str_replace('_', '-', $vars['view']->name);
}

