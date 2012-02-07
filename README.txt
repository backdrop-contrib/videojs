
Dependencies
------------

* CCK (Content module)
* FileField

Install
-------

1) Copy the videojs folder to the modules folder in your installation. Usually
   this is sites/all/modules.

2) Download Video.js from http://videojs.com.

3) In your Drupal site, enable the module under Administer -> Site building ->
   Modules (/admin/build/modules).

4) Add or configure a FileField under Administer -> Content management ->
   Content types -> [type] -> Manage Fields
   (admin/content/node-type/[type]/fields). Restrict the upload extension to
   only allow the video HTML5 extension. It's also a good idea to enable the Description
   option, as this can be used to label your files when they are displayed. Set the "Number
   of values" to at least 2.

5) Configure the display of your FileField to use "Video.js player".

6) Create a piece of content with the configured field. Give the file a
   description that will be used as the file label in the playlist.

7) Create a poster image and upload the image in the FileField field created in step #4.

Support
-------

Heshan <heshan at heidisoft dot com>
