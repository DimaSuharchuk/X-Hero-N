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
  foreach (_get_items(FALSE) as $nid) {
    node_delete($nid);
    $count++;
  }

  // @todo Remove this code if not only Item nodes were created.
  // Reset index of "node" table.
  db_truncate('node')->execute();

  // Show message about count of deleted items.
  drupal_set_message(t('Deleted %count Items.', ['%count' => $count]));
}
