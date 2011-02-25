<?php

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
    <?php if($mimetype == 'video/mp4' || $mimetype == 'video/flv') $flash =  $filepath;?>
    <?php $videojs_sources .= "<source src=\"$filepath\" type='$mimetype; codecs=\"" . $codecs[$mimetype] . "\"' />"; ?>
    <?php endif; ?>
    <?php endforeach; ?>
    <?php print $videojs_sources; ?>
        <!-- Flash Fallback. Use any flash video player here. Make sure to keep the vjs-flash-fallback class. -->
    <?php
        if (module_exists('swftools')) {
          $options = array(
            'params' => array(
              'width' => variable_get('videojs_width', 640),
              'height' => variable_get('videojs_height', 264),
            ),
            'othervars' => array(
              //@todo: swftools bug, can't enable this until they fix their pathing for the images.
              'image' => $poster,
            ),
          );
          $themed_output = swf($flash, $options);
        } elseif (module_exists('flowplayer')) {
          // kjh: use a playlist to display the thumbnail if not auto playing
          if (!empty($poster)) {
            $options = array(
              'playlist' => array($poster,
                array('url' => urlencode($flash),
                  'autoPlay' => FALSE,
                  'autoBuffering' => TRUE,
                ),),);
          } else {
            $options = array(
              'clip' => array('url' => urlencode($flash),
                'autoPlay' => FALSE,
                'autoBuffering' => TRUE,
              ),);
          }

          $themed_output = theme(
                  'flowplayer',
                  $options,
                  // adding 24px to height #973636
                  array('style' => 'width:' . variable_get('videojs_width', 640) . 'px;height:' . variable_get('videojs_height', 264) + 24 . 'px;')
          );
        }
    ?>
  </video>
</div>
<!-- End VideoJS -->