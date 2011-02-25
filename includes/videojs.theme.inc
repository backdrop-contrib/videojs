<?php


/**
 * Theme and preprocess functions for the videojs module.
 */

/**
 * Preprocess function for videojs.tpl.php when using a playlist.
 */
function template_preprocess_videojs_formatter_videojs(&$vars) {
  videojs_add();
  $vars['items'] = array();
  $field_name = $vars['element']['#field_name'];
  $node = $vars['element']['#node'];
  $number = 0;
  foreach ($node->$field_name as $item) {
    $vars['items'][] = $item;
  }
  $vars['player_id'] = 'videojs-' . $vars['element']['#node']->nid . '-' . str_replace('_', '-', $vars['element']['#field_name']);
    // Grab any poster image from a field named videojs_poster
  if (!empty($node->field_videojs_poster)) {
    $image = $node->field_videojs_poster[0]; // take the first image from videojs_poster field
    $vars['poster'] = file_create_url($image['filepath']);
  }
}

/**
 * Preprocess function for videojs.tpl.php when displaying a view as a playlist.
 */
function template_preprocess_videojs_view(&$vars) {
  videojs_add();
  $vars['player_id'] = 'videojs-view-' . str_replace('_', '-', $vars['view']->name);
}
