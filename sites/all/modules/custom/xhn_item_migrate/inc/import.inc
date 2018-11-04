<?php
/**
 * @file
 * Import functionality.
 */

/**
 * Create batch queue for import items.
 */
function batch_items_import($form, $form_state) {
  $file = file_load($form_state['values']['json']);
  $data = json_decode(file_get_contents($file->uri));

  $operations = [];

  foreach ($data as $i => $item) {
    $operations[] = [
      'batch_items_import_batch',
      [
        $item,
      ],
    ];
  }

  $batch = [
    'operations' => $operations,
    'finished' => 'batch_items_batch_import_finished',
  ];

  batch_set($batch);
}

/**
 * Create new Item entities from json data.
 *
 * @param $artifact
 *  Data from json for saving to new Item entity.
 * @param $context
 *  Batch context.
 */
function batch_items_import_batch($artifact, &$context) {
  // Get Item entity properties, not fields.
  $item_entity_properties = array_keys(entity_get_property_info('item')['properties']);

  // Before using entity wrapper we need to create and save new entity.
  $new_item = entity_create('item', ['type' => 'item']);
  entity_save('item', $new_item);

  // Use wrapper for easy filling values.
  $item_wrapper = entity_metadata_wrapper('item', $new_item);

  // Set properties.
  foreach ($artifact as $property_name => $value) {
    if (in_array($property_name, $item_entity_properties)) {
      $item_wrapper->$property_name->set($value);
    }
  }

  /**
   * Fields.
   */
  // Icon.
  $icon_content = file_get_contents($artifact->icon_base64);
  $file_temp = file_save_data($icon_content, "public://item_icons/{$artifact->icon_name}", FILE_EXISTS_REPLACE);
  $item_wrapper->field_icon->set(
    [
      'fid' => $file_temp->fid,
      'filename' => $file_temp->filename,
      'alt' => $artifact->name,
      'filemime' => $file_temp->filemime,
      'uid' => 1,
      'uri' => $file_temp->uri,
      'status' => 1,
    ]
  );
  // Description.
  if (isset($artifact->description)) {
    $item_wrapper->field_description->set([
      'format' => 'full_html',
      'value' => $artifact->description,
    ]);
  }
  // Shop.
  if (isset($artifact->shop_ids)) {
    $item_wrapper->field_shop->set($artifact->shop_ids);
  }
  // Requires.
  if (isset($artifact->field_requires)) {
    $requires_ids = [];
    foreach ($artifact->field_requires as $name) {
      $item_id = db_select('eck_item', 'i')
        ->fields('i', ['id'])
        ->condition('name', $name)
        ->execute()
        ->fetchField();
      if ($item_id) {
        $requires_ids[] = $item_id;
      }
      else {
        drupal_set_message('Not found %name in DB.', ['%name' => $name]);
      }
    }
    $item_wrapper->field_requires->set($requires_ids);
  }

  // Save entity with values.
  $item_wrapper->save();

  // Count iterations.
  if (!$context['results']['count']) {
    $context['results']['count'] = 0;
  }
  $context['results']['count']++;
}

/**
 * Show message with count of Items created.
 *
 * @param bool $success
 *  Batch finished success.
 * @param $results
 *  Batch results.
 */
function batch_items_batch_import_finished($success, $results) {
  if ($success) {
    drupal_set_message(t('Created @count items', ['@count' => $results['count']]));
  }
}
