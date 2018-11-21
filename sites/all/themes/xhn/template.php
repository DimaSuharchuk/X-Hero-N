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
 * Implements template_preprocess_field.
 *
 * {@inheritdoc}
 */
function xhn_preprocess_field(&$variables) {
  switch ($variables['element']['#field_name']) {
    case 'field_shop':
      $shops = [];
      foreach ($variables['items'] as $item) {
        $shops[] = $item['#markup'];
      }
      $variables['items'] = [
        '#markup' => implode(' / ', $shops),
      ];
      $variables['label'] = 'Находится в';
      break;

    case 'field_requires':
      foreach ($variables['items'] as $key => $item) {
        $variables['items'][$key] = node_view($item['#item']['entity'], 'icon');
        $variables['items'][$key]['title'] = [
          '#type' => 'item',
          '#markup' => $variables['items'][$key]['#node']->title,
        ];
      }
      break;
  }
}

/**
 * Implements theme_field__field_type().
 *
 * {@inheritdoc}
 */
function xhn_field__taxonomy_term_reference($variables) {
  $output = '';

  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div class="field-label">' . $variables['label'] . ':&nbsp;</div>';
  }

  // Render the items.
  if (isset($variables['items'][0]) && is_array($variables['items'][0])) {
    $output .= ($variables['element']['#label_display'] == 'inline') ? '<ul class="links inline">' : '<ul class="links">';
    foreach ($variables['items'] as $delta => $item) {
      $output .= "<li class='taxonomy-term-reference-{$delta}' {$variables['item_attributes'][$delta]}>" . drupal_render($item) . '</li>';
    }
    $output .= '</ul>';
  }
  else {
    $output .= drupal_render($variables['items']);
  }

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . (!in_array('clearfix', $variables['classes_array']) ? ' clearfix' : '') . '">' . $output . '</div>';

  return $output;
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

/**
 * Implements template_preprocess_HOOK.
 *
 * {@inheritdoc}
 * @throws \Exception
 */
function xhn_preprocess_calculator(&$vars) {
  // Path to images directory in theme.
  $images_path = drupal_get_path('theme', 'xhn') . '/images';

  $items = [];

  // Load icons for chosen nodes for calculator.
  if ($vars['node_ids']) {
    foreach ($vars['node_ids'] as $node_id) {
      // This check needs, because removing last item in calculator returns node ID 0.
      if ($node_id > 0) {
        $items[] = node_view(node_load($node_id), 'icon');
      }
    }
  }

  // Set default "empty" images for empty cells in calculator.
  for ($i = 0; $i < 6; $i++) {
    // Skip setting "empty images" if some cells filled with icons.
    if (!empty($items[$i])) {
      continue;
    }
    // Else set "empty" images.
    $items[] = [
      '#markup' => theme('image', ['path' => $images_path . '/empty.jpg']),
    ];
  }

  // Save themed calculator's images to variable.
  $vars['items'] = $items;
}
