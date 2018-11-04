<?php
/**
 * @file
 * Items remove functionality.
 */

/**
 * Items remove callback.
 */
function batch_items_remove() {
  // Really removing items doesn't need a batch.
  $count = 0;
  foreach (_get_items() as $entity) {
    entity_delete('item', $entity->id);
    $count++;
  }

  // Reset index of "eck_item" table.
  db_truncate('eck_item')->execute();

  // Show message about count of deleted items.
  drupal_set_message(t('Deleted %count Items.', ['%count' => $count]));
}
