Video.js HTTP Live Streaming
============================

HTTP Live Streaming is developer by Apply to allow iOS devices like the iPad,
iPod Touch or iPhone to select a video stream that suits the device capabilities
and available bandwidth. Each stream is segmented in multiple MPEG stream files
and has an m3u8 index files. Another m3u8 file lists these m3u8 files together
with the bitrate of these alternatives. This m3u8 master index file is used
by the iOS video player to select the right m3u8 file. When the available
bandwidth changes during playback, the device may switch to another stream.

This module intercepts m3u8 files supplied to the Video.js module.
It replaces these files with one new dynamically generated file file that makes
bandwidth switching available to iOS devices.

This module does not provide an administrative interface and has no
settings. It works automatically when it is enabled.

Requirements
------------

1. Multiple m3u8 files need to be supplied to Video.js. When just one m3u8 file
   is supplied there is no choice for the iOS player, so no master index is
   needed.
2. The files need to have the filemime application/vnd.apple.mpegurl.
3. The filenames need to contain `<number>k` in the filename, such as
   `sample-640k.m3u8`. This number is used to indicate the bandwidth
   to the client.

You can use the Video module with the Zencoder transcoder to create files
that are compatible with the Video.js module.

Also see
--------

- https://app.zencoder.com/docs/guides/encoding-settings/http-live-streaming
- https://developer.apple.com/resources/http-streaming/
- http://drupal.org/project/video
