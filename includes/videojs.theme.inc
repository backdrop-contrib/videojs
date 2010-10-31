<?php

// $Id$

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
}

/**
 * Preprocess function for videojs.tpl.php when displaying a view as a playlist.
 */
function template_preprocess_videojs_view_playlist(&$vars) {
  videojs_add();
  $vars['player_id'] = 'videojs-view-' . str_replace('_', '-', $vars['view']->name);
}
