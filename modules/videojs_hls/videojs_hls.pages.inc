<?php
/**
 * @file
 * Menu callbacks for the Video.js HTTP Live Streaming module.
 */

/**
 * Menu callback for the m3u8/% path.
 */
function videojs_hls_render($filedata) {
  if (empty($filedata)) {
    drupal_not_found();
    exit;
  }

  $files = explode('|', rawurldecode($filedata));

  $return = array();
  $matches = array();

  foreach ($files as $file) {
    if (!preg_match('#(\d+)k#i', $file, $matches)) {
      continue;
    }
    $bw = ($matches[1] * 1000);
    $return[$bw] = '#EXT-X-STREAM-INF:PROGRAM-ID=1, BANDWIDTH=' . $bw . "\n" . file_create_url($file);
  }

  if (empty($return)) {
    drupal_not_found();
    exit;
  }

  // Sort the files by bandwidth, lowest first.
  ksort($return);

  array_unshift($return, '#EXTM3U');

  return implode("\n", $return);
}

/**
 * Delivery callback for the m3u8/% path.
 */
function videojs_hls_deliver($page_callback_result) {
  if (is_int($page_callback_result)) {
    drupal_deliver_html_page($page_callback_result);
    return;
  }

  drupal_add_http_header('Content-Type', 'application/vnd.apple.mpegurl; charset=utf-8');
  echo $page_callback_result;
}
