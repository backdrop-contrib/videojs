# Video.js

Video.js is a HTML5-based video player. This means that videos can be played on nearly all devices and
operating systems, provided the right codecs are used.

This module is a support module for `Video.js` -- you can use the bundled
version, CDN version, or download your own version and this module integrates it
with the File, Link and Video modules after you've installed it.

## Includes

- Support for Video.js 4.0.0+ (CDN and Bundled library default to 8.17.3)
- Support for subtitle tracks.
- Support for looping, hiding player controls and changing preload behavior.
- Setup above settings for each field and view individually, as well as width
  and height of the player.
- Load the Video.js files from the Video.js CDN - downloading and installing the
  player is not necessary.
- Locate the Video.js files using the Libraries API.
- Sub-module: Video.js HTTP Live Streaming. Extends the functionality of
  Video.js by combining multiple m3u8 files into one file that can be used for
  bandwidth switching.
- Sub-module: VideoJS Filter. Provides a filter so videos can be inserted into
  any entity with a textarea field: nodes, blocks and so on.

## Required dependencies

None

## Optional dependencies

- Backdrop core File module
- Backdrop core Link module
- [Libraries API 2](http://backdropcms.org/project/libraries)

## Installation

1. Install the Video.js module by copying the sources to a modules directory,
   such as `modules`.
2. In your Backdrop site, enable the module.
3. If you plan to use the bundled or CDN version of the library, skip this step.
   If you'd like to download your own version of the library, download it from
   https://videojs.com. Extract the module to `libraries/video-js` and make
   sure that `libraries/video-js/video.js` exists.
4. If not yet created, create a File field for one of your content types at
   **Structure -> Content types -> [type] -> Manage fields**. Make sure the
   allowed extensions contain only HTML5 video extensions, such as mp4,  webm,
   mov and ogv. Use the `Number of values` setting to allow users to upload
   alternative versions of the same video, for instance MP4 and Ogg. To allow
   users to upload a poster image, also allow png, gif or jpg.
5. At the Manage display tab, select `Video.js` for your File field.
6. Create a piece of content with the configured field.
7. Create a poster image and upload the image in the file field field created in step #4.

Note: instead of a File field, you also use a Link field from the Link module. The module detects the type of the file from the extension. If the link contains no extension, write the mime type (like video/mp4) in the title field of the link.

## Poster images from a separate field

It is possible to display images uploaded to an image field as the video poster image. After you added an image field to your content type, edit the display settings of the Video.js field and specify the image field in the "Poster image field" setting.

## Installation with the Video module

If you are using the Video module, you can't configure the player at the `Manage display` tab. Instead, select Video.js at the Players tab of the Video settings page (admin/config/media/video/players).

## Subtitle tracks

To add subtitles to your video, upload a VTT file to the file field, or link to a VTT file when using a Link field. Enter the language name or two-letter code in the description field. Use the English or local language
name.

## Loading Video.js from code

The Video.js module exposes the theme function 'videojs' to write a Video.js player in code. The theme function has the following variables:

- `items`: Array of playable items. Each item in the array must be an array with the following keys:
  - `uri` (required): URI of the file. It must be an audio file, video file, image file (for the poster image) or VTT file (for subtitles).
  - `filemime` (required): mime type of the file.
  - `langcode` (vtt only): language code.
  - `label` (vtt only): label of the track.
  - `default` (vtt only): whether the track is selected by default.
  - `charset` (vtt only): the character set of the track.
  - `kind` (vtt only): the kind of track: subtitles, captions, descriptions, chapters or metadata. Default: subtitles.
- `player_id` (required): ID of the player. Must be unique on the page.
- `attributes`: array with the following optional values:
  - `width`: width of the player.
  - `height`: height of the player.
  - `loop`: boolean to loop the video.
  - `hidecontrols`: boolean to hide the player controls.
  - `autoplay`: boolean to start playback on load.
  - `preload`: preload mode. either none, metadata or auto.
- `posterimage_style` (optional): set to the machine name of an image style to transform the poster image using that style.

### Example

```
    echo theme('videojs', array(
      'items' => array(
        array(
          'uri' => 'public://test.mp4',
          'filemime' => 'video/mp4',
        ),
        array(
          'uri' => 'public://test.webm',
          'filemime' => 'video/webm',
        ),
        array(
          'uri' => 'public://test-poster.jpg',
          'filemime' => 'image/jpeg',
        ),
        array(
          'uri' => 'public://test-en.vtt',
          'filemime' => 'text/vtt',
          'langcode' => 'en',
          'description' => 'English',
          'default' => TRUE,
        ),
        array(
          'uri' => 'public://test-nl.vtt',
          'filemime' => 'text/vtt',
          'langcode' => 'nl',
          'description' => 'Nederlands',
        ),
        array(
          'uri' => 'public://test-fy.vtt',
          'filemime' => 'text/vtt',
          'langcode' => 'fy',
          'description' => 'Frysk',
        ),
      ),
      'player_id' => 'test-video',
      'posterimage_style' => 'thumbnail',
      'attributes' => array(
        'width' => 640,
        'height' => 360,
        'loop' => FALSE,
        'autoplay' => TRUE,
        'preload' => 'none',
        'hidecontrols' => FALSE,
      ),
    ));
```

## Support

- Report bugs for this *Backdrop module* at `<https://github.com/backdrop-contrib/videojs>`.
- Report bugs for the *player* at `<https://github.com/videojs/video.js/issues>`.

## Maintainers

- [Laryn Kragt Bakker](https://github.com/laryn)
- This module is seeking additional maintainers.

## Credits

- Ported to Backdrop CMS by [Herb v/d Dool](https://github.com/herbdool/).

Originally written for Drupal by

- Heshan Wanigasooriya (https://www.drupal.org/u/heshanlk)
- Jorrit Schippers (https://www.drupal.org/u/jorrit)

## License

This project is GPL v3 software. See the LICENSE.txt file in this directory for complete text.
