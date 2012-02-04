<?php
/**
 * Provide the HTML output of the videojs audio player.
 */

$attrs = '';
if (!empty($autoplay)) {
  $attrs .= ' autoplay="autoplay"';
}
if (!empty($poster)) {
  $attrs .= ' poster="'. check_plain($poster) .'"';
}

if (!empty($items)): ?>
<div class="video-js-box <?php print variable_get('videojs_skin', 'default') ?>" id="<?php print $player_id; ?>">
  <video id="<?php print $player_id; ?>-video" class="video-js" width="<?php print($width) ?>" height="<?php print($height) ?>" controls="controls" preload="auto"<?php echo $attrs; ?>>
<?php foreach ($items as $item): ?>
    <source src="<?php print(file_create_url($item['uri'])) ?>" type="<?php print check_plain($item['videotype']) ?>" />
<?php endforeach; ?>
<?php if (!empty($flash_player)): ?>
    <div class="vjs-flash-fallback"><?php echo $flash_player; ?></div>
<?php elseif(!empty($flash)): ?>
    <object class="vjs-flash-fallback" width="<?php print($width) ?>" height="<?php print($height) ?>" type="application/x-shockwave-flash" data="http://releases.flowplayer.org/swf/flowplayer-3.2.5.swf">
      <param name="movie" value="http://releases.flowplayer.org/swf/flowplayer-3.2.5.swf" />
      <param name="allowfullscreen" value="true" />
      <param name="flashvars" value="config={'playlist': [ <?php if(isset($poster)) print("'".$poster."',"); ?> {'url': '<?php print($flash) ?>', 'autoPlay':false, 'autoBuffering':true} ]}" />
      <embed id="flash-<?php print $player_id; ?>"
                 name="flash-<?php print $player_id; ?>"
                 src="http://releases.flowplayer.org/swf/flowplayer-3.2.5.swf"
                 width="<?php print($width) ?>"
                 height="<?php print($height) ?>"
                 type="application/x-shockwave-flash"
                 allowscriptaccess='always'
                 allowfullscreen='true'
                 flashvars="config={'playlist': [ <?php if(isset($poster)) print("'".$poster."',"); ?> {'url': '<?php print($flash) ?>', 'autoPlay':false, 'autoBuffering':true} ]}"
                 />
<?php if(!empty($poster)): ?>
      <img src="<?php print($poster) ?>" width="<?php print($width) ?>" height="<?php print($height) ?>" alt="Poster Image" title="No video playback capabilities." />
<?php endif; ?>
    </object>
<?php endif; ?>
  </video>
</div>
<?php endif;
