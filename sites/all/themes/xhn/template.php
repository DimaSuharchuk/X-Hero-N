<?php

/**
 * Implements template_preprocess_node.
 *
 * {@inheritdoc}
 */
function xhn_preprocess_node(&$variables) {
  switch ($variables['view_mode']) {
    case 'icon':
      $variables['page'] = TRUE;
      break;
  }
}

/**
 * Implements template_preprocess_HOOK.
 *
 * {@inheritdoc}
 */
function xhn_preprocess_artifact_info(&$vars) {
  $vars['target_node'] = node_view(node_load($vars['nid']), 'icon');

  $requires = [];
  foreach ($vars['requires'] as $nid) {
    $requires[] = node_view(node_load($nid), 'icon');
  }
  $vars['requires'] = $requires;

  $used_for = [];
  foreach ($vars['used_for'] as $nid) {
    $used_for[] = node_view(node_load($nid), 'icon');
  }
  $vars['used_for'] = $used_for;
}
