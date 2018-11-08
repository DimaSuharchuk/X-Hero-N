<?php

/**
 * @file
 * xhn_taxonomy_shop.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function xhn_taxonomy_shop_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
