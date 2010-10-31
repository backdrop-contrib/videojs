<?php
// $Id$

/**
 * Provide the HTML output of the videojs audio player.
 */
?>
 <!-- Begin VideoJS -->
  <div class="video-js-box" id="<?php print $player_id; ?>">
    <!-- Using the Video for Everybody Embed Code http://camendesign.com/code/video_for_everybody -->
    <video id="<?php print $player_id; ?>" class="video-js" width="<?php print(variable_get('videojs_width', 640))?>" height="<?php print(variable_get('videojs_height', 264))?>" controls="controls" preload="auto" poster="">
      <?php foreach ($items as $item):?>
      <?php $filepath = file_create_url($item['filepath']); ?>
        <?php if($item['filemime'] == 'video/mp4') ?>
          <source src="<?=$filepath?>" type='video/mp4; codecs="avc1.42E01E, mp4a.40.2"' />
        <?php if($item['filemime'] == 'application/octet-stream') ?>
          <source src="<?=$filepath?>" type='video/webm; codecs="vp8, vorbis"' />
        <?php if($item['filemime'] == 'application/ogg' || $item['filemime'] == 'video/ogg') ?>
          <source src="<?=$filepath?>" type='video/ogg; codecs="theora, vorbis"' />
      <?php endforeach; ?>
      <!-- Flash Fallback. Use any flash video player here. Make sure to keep the vjs-flash-fallback class. -->
      <!-- @TODO: Add Flowplayer on SWFTools or Flowplayer API modules -->
    </video>
  </div>
  <!-- End VideoJS -->