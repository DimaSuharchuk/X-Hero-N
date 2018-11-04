<?php
/**
 * @file
 * Export functionality.
 */

/**
 * Create batch queue for export items.
 */
function batch_items_export() {
  $operations = [];

  foreach (_get_items() as $i => $item) {
    $operations[] = [
      'batch_items_export_batch',
      [
        $item,
      ],
    ];
  }

  $batch = [
    'operations' => $operations,
    'finished' => 'batch_items_batch_export_finished',
  ];

  batch_set($batch);
}

/**
 * Fill arrays with item's properties and fields values.
 *
 * @param $artifact
 *  Loaded item entity.
 * @param $context
 *  Batch context.
 */
function batch_items_export_batch($artifact, &$context) {
  // Get Item entity properties, not fields.
  $item_properties = array_keys(entity_get_property_info('item')['properties']);
  // Remove useless properties.
  $item_properties = array_diff($item_properties, ['id', 'type']);

  // Fill properties values to info array.
  $item_info = [];
  foreach ($item_properties as $property_name) {
    if (!empty($artifact->$property_name) && $property_name !== 'id') {
      $item_info[$property_name] = $artifact->$property_name;
    }
  }

  /**
   * Fields.
   */
  // Icon.
  $item_info['icon_name'] = $artifact->field_icon[LANGUAGE_NONE][0]['filename'];
  $icon_uri = file_get_contents($artifact->field_icon[LANGUAGE_NONE][0]['uri']);
  $item_info['icon_base64'] = 'data:image/png;base64,' . base64_encode($icon_uri);
  // Description.
  if (!empty($artifact->field_description)) {
    $item_info['description'] = $artifact->field_description[LANGUAGE_NONE][0]['value'];
  }
  // Taxonomy shop.
  if (!empty($artifact->field_shop)) {
    $item_info['shop_ids'] = [];
    foreach ($artifact->field_shop[LANGUAGE_NONE] as $item) {
      $item_info['shop_ids'][] = $item['tid'];
    }
  }
  // Requires.
  if (!empty($artifact->field_requires)) {
    $item_info['field_requires'] = [];
    $artifact_wrapper = entity_metadata_wrapper('item', $artifact);
    $field_requires = $artifact_wrapper->field_requires->value();
    foreach ($field_requires as $require_item) {
      $item_info['field_requires'][] = $require_item->name;
    }
  }

  // Save iteration's data to context.
  $context['results'][] = $item_info;
}

/**
 * Export batch finished callback.
 *
 * @param bool $success
 *  TRUE if batch finished without errors.
 * @param array $results
 *  Array with Items prepared info for saving.
 */
function batch_items_batch_export_finished($success, $results) {
  if ($success) {
    // Create json with artifacts prepared data and link for download.
    $file_path = 'public://items_export.json';
    file_put_contents($file_path, json_encode($results));

    $download_link = l('Download json', file_create_url($file_path), ['attributes' => ['download' => TRUE]]);
    drupal_set_message($download_link);
  }
  else {
    drupal_set_message('Process interrupted', 'error');
  }
}
