<!-- Begin VideoJS -->
<?php if (count($items) > 0): ?>
  <div class="video-js-box <?php print variable_get('videojs_skin', 'default') ?>" id="<?php print $player_id; ?>">
    <!-- Using the Video for Everybody Embed Code http://camendesign.com/code/video_for_everybody -->
    <video id="<?php print $player_id; ?>-video" class="video-js" width="<?php print($width) ?>" height="<?php print($height) ?>" controls="controls" preload="auto" poster="<?php print($poster) ?>">
      <?php foreach ($items as $item): ?>
        <?php $filepath = file_create_url($item['uri']); ?>
        <source src="<?php print(file_create_url($item['uri'])) ?>" type="<?php print($item['videotype']) ?>" />
      <?php endforeach; ?>
      <!-- Flash Fallback. Use any flash video player here. Make sure to keep the vjs-flash-fallback class. -->
      <?php
      if (isset($flash_player)):
        print($flash_player);
      else:
        ?>
        <object class="vjs-flash-fallback" width="<?php print($width) ?>" height="<?php print($height) ?>" type="application/x-shockwave-flash"
                data="http://releases.flowplayer.org/swf/flowplayer-3.2.5.swf">
          <param name="movie" value="http://releases.flowplayer.org/swf/flowplayer-3.2.5.swf" />
          <param name="allowfullscreen" value="true" />
          <param name="flashvars" value="config={'playlist': [ '<?php print($poster) ?>', {'url': '<?php print($flash) ?>', 'autoPlay':false, 'autoBuffering':true} ]}" />
          <embed id="flash-<?php print $player_id; ?>"
                 name="flash-<?php print $player_id; ?>"
                 src="http://releases.flowplayer.org/swf/flowplayer-3.2.5.swf"
                 width="<?php print($width) ?>"
                 height="<?php print($height) ?>"
                 type="application/x-shockwave-flash"
                 allowscriptaccess='always'
                 allowfullscreen='true'
                 flashvars="config={'playlist': [ '<?php print($poster) ?>', {'url': '<?php print($flash) ?>', 'autoPlay':false, 'autoBuffering':true} ]}"
                 />
          <!-- Image Fallback. Typically the same as the poster image. -->
          <img src="<?php print($poster) ?>" width="<?php print($width) ?>" height="<?php print($height) ?>" alt="Poster Image"
               title="No video playback capabilities." />
        </object>
      <?php endif; //$flash_player   ?>
    </video>
  </div>
<?php endif; ?>
<!-- End VideoJS -->

