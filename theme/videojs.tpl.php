<?php
// $Id$

/**
 * Provide the HTML output of the videojs audio player.
 */
?>
<!-- Begin VideoJS -->
<div class="video-js-box" id="<?php print $player_id; ?>">
  <!-- Using the Video for Everybody Embed Code http://camendesign.com/code/video_for_everybody -->
  <video id="<?php print $player_id; ?>" class="video-js" width="<?php print(variable_get('videojs_width', 640)) ?>" height="<?php print(variable_get('videojs_height', 264)) ?>" controls="controls" preload="auto" poster="<?php print $poster; ?>">
    <?php //dd($items); ?>
    <?php static $videojs_sources; ?>
    <?php $codecs = array('video/mp4' => 'avc1.42E01E, mp4a.40.2', 'video/webm' => 'vp8, vorbis', 'video/ogg' => 'theora, vorbis', 'video/quicktime' => 'avc1.42E01E, mp4a.40.2'); ?>
    <?php foreach ($items as $item): ?>
    <?php $filepath = file_create_url($item['filepath']); ?>
    <?php $mimetype = $item['filemime']; ?>
    <?php if (array_key_exists($mimetype, $codecs)): ?>
    <?php $mimetype = ($mimetype == 'video/quicktime') ? 'video/mp4' : $mimetype; ?>
    <?php $videojs_sources .= "<source src=\"$filepath\" type='$mimetype; codecs=\"" . $codecs[$mimetype] . "\"' />"; ?>
    <?php endif; ?>
    <?php endforeach; ?>
    <?php print $videojs_sources; ?>
    <!-- Flash Fallback. Use any flash video player here. Make sure to keep the vjs-flash-fallback class. -->
    <!-- @TODO: Add Flowplayer on SWFTools or Flowplayer API modules -->
  </video>
</div>
<!-- End VideoJS -->