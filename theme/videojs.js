
/**
 * @file
 * Drupal behaviors for the videojs audio player.
 */

(function ($) {
  Drupal.behaviors.videojs = {
    attach: function() {
      // Must come after the video.js library

      // Add VideoJS to all video tags on the page when the DOM is ready
      VideoJS.autoSetup();

    }
  }
})(jQuery);
