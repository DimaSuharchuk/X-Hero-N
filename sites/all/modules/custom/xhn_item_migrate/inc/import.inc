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
  // Get node fields name.
  $fields = array_keys(field_info_instances('node', 'item'));
  // Remove special fields from list.
  $special_fields = [
    'field_icon',
    'field_shop',
    'field_requires',
    'field_description',
    'field_active',
    'field_passive',
  ];
  $fields = array_diff($fields, $special_fields);

  // Before using entity wrapper we need to create and save new node.
  $new_item = entity_create('node', ['type' => 'item']);
  // PathAuto enable.
  $new_item->path = ['pathauto' => 1];
  entity_save('node', $new_item);

  // Use wrapper for easy filling values.
  $item_wrapper = entity_metadata_wrapper('node', $new_item);

  // Set properties.
  foreach ($artifact as $field_name => $value) {
    if (in_array($field_name, $fields)) {
      $item_wrapper->{$field_name}->set($value);
    }
  }

  /**
   * Special fields.
   */
  // Title.
  $item_wrapper->title->set($artifact->title);
  // Icon.
  $icon_content = file_get_contents($artifact->icon_base64);
  $file_temp = file_save_data($icon_content, "public://item_icons/{$artifact->icon_name}", FILE_EXISTS_REPLACE);
  $item_wrapper->field_icon->set(
    [
      'fid' => $file_temp->fid,
      'filename' => $file_temp->filename,
      'alt' => $artifact->title,
      'title' => $artifact->title,
      'filemime' => $file_temp->filemime,
      'uid' => 1,
      'uri' => $file_temp->uri,
      'status' => 1,
    ]
  );
  // Description.
  if (isset($artifact->field_description)) {
    $item_wrapper->field_description->set([
      'format' => 'full_html',
      'value' => $artifact->field_description,
    ]);
  }
  // Active.
  if (isset($artifact->field_active)) {
    $item_wrapper->field_active->set([
      'format' => 'full_html',
      'value' => $artifact->field_active,
    ]);
  }
  // Passive.
  if (isset($artifact->field_passive)) {
    $item_wrapper->field_passive->set([
      'format' => 'full_html',
      'value' => $artifact->field_passive,
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
      $item_id = db_select('node', 'n')
        ->fields('n', ['nid'])
        ->condition('title', $name)
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
  if (!isset($context['results']['count'])) {
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
