<?php
/**
 * @file
 * This file will be used to keep all utility functions.
 */

/**
 * Helper functions for the Video.js module.
 *
 * These functions are put in a utility class so they will only be
 * auto-loaded when needed.
 */
class videojs_utility {
  public static function getDisplaySettingsForm(array &$element, array $values = NULL) {
    if ($values === NULL) {
      $values = self::getDefaultDisplaySettings();
    }

    $element['width'] = array(
      '#type' => 'textfield',
      '#title' => t('Player width'),
      '#default_value' => !empty($values['width']) ? intval($values['width']) : '',
      '#element_validate' => array('_element_validate_integer_positive'),
      '#maxlength' => 10,
      '#size' => 10,
    );

    $element['height'] = array(
      '#type' => 'textfield',
      '#title' => t('Player height'),
      '#default_value' => !empty($values['height']) ? intval($values['height']) : '',
      '#element_validate' => array('_element_validate_integer_positive'),
      '#maxlength' => 10,
      '#size' => 10,
    );

    $element['autoplay'] = array(
      '#type' => 'checkbox',
      '#title' => t('Auto-play files on page load'),
      '#description' => t('Use caution when combining this option with multiple players on the same page.'),
      '#default_value' => !empty($values['autoplay']),
    );

    $element['loop'] = array(
      '#type' => 'checkbox',
      '#title' => t('Loop playback'),
      '#default_value' => !empty($values['loop']),
    );

    $element['hidecontrols'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide controls'),
      '#default_value' => !empty($values['hidecontrols']),
    );

    $element['preload'] = array(
      '#type' => 'select',
      '#title' => t('Preload behavior'),
      '#options' => array(
        'auto' => t('Automatic preloading'),
        'metadata' => t('Only metadata'),
        'none' => t('No preloading'),
      ),
      '#default_value' => !empty($values['preload']) ? $values['preload'] : 'auto',
    );
  }

  public static function getDisplaySettingsFormResults(array $values) {
    return array(
      'loop' => !empty($values['loop']),
      'autoplay' => !empty($values['autoplay']),
      'hidecontrols' => !empty($values['hidecontrols']),
      'width' => !empty($values['width']) ? intval($values['width']) : NULL,
      'height' => !empty($values['height']) ? intval($values['height']) : NULL,
      'preload' => !empty($values['preload']) ? $values['preload'] : NULL,
    );
  }

  public static function getDefaultDisplaySettings() {
    return array(
      'loop' => variable_get('videojs_loop', FALSE),
      'hidecontrols' => variable_get('videojs_hidecontrols', FALSE),
      'autoplay' => variable_get('videojs_autoplay', FALSE),
      'width' => variable_get('videojs_width', 640),
      'height' => variable_get('videojs_height', 360),
      'preload' => variable_get('videojs_preload', 'auto'),
    );
  }

  public static function getDisplaySettings(array $input = array()) {
    $settings = self::getDefaultDisplaySettings();

    if (empty($input)) {
      return $settings;
    }

    foreach ($input as $k => $v) {
      if ($v !== NULL && array_key_exists($k, $settings)) {
        $settings[$k] = $v;
      }
    }

    return $settings;
  }

  /**
   * Tries to find a language based on the input
   *
   * @param $input
   *   String containing a language code or language name.
   *
   * @return
   *   NULL if nothing found, array with code and name if found.
   */
  public static function resolveLanguage($input) {
    if (empty($input) || !is_string($input)) {
      return NULL;
    }
    $input = trim($input);
    if (strlen($input) < 2) {
      return NULL;
    }

    include_once DRUPAL_ROOT . '/includes/iso.inc';
    $languages = _locale_get_predefined_list();

    if (strlen($input) === 2 && isset($languages[strtolower($input)])) {
      $input = strtolower($input);
      return array($input, isset($languages[$input][1]) ? $languages[$input][1] : $languages[$input][0]);
    }

    foreach ($languages as $code => $lang) {
      if ($lang[0] === $input || (isset($lang[1]) && $lang[1] === $input)) {
        return array($code, $input);
      }
    }

    return NULL;
  }
}
