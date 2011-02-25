
/**
 * @file
 * Drupal behaviors for the videojs audio player.
 */

(function ($) {

  // Must come after the video.js library

  // Add VideoJS to all video tags on the page when the DOM is ready
  VideoJS.setupAllWhenReady();

/* ============= OR ============ */

// Setup and store a reference to the player(s).
// Must happen after the DOM is loaded
// You can use any library's DOM Ready method instead of VideoJS.DOMReady

/*
    VideoJS.DOMReady(function(){

      // Using the video's ID or element
      var myPlayer = VideoJS.setup("example_video_1");

      // OR using an array of video elements/IDs
      // Note: It returns an array of players
      var myManyPlayers = VideoJS.setup(["example_video_1", "example_video_2", video3Element]);

      // OR all videos on the page
      var myManyPlayers = VideoJS.setup("All");

      // After you have references to your players you can...(example)
      myPlayer.play(); // Starts playing the video for this player.
    });
    */

/* ========= SETTING OPTIONS ========= */

// Set options when setting up the videos. The defaults are shown here.

/*
    VideoJS.setupAllWhenReady({
      controlsBelow: false, // Display control bar below video instead of in front of
      controlsHiding: true, // Hide controls when mouse is not over the video
      defaultVolume: 0.85, // Will be overridden by user's last volume if available
      flashVersion: 9, // Required flash version for fallback
      linksHiding: true // Hide download links when video is supported
    });
    */

// Or as the second option of VideoJS.setup

/*
    VideoJS.DOMReady(function(){
      var myPlayer = VideoJS.setup("example_video_1", {
        // Same options
      });
    });
    */


})(jQuery);
