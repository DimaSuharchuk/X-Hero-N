<?php

/**
 * Define path to theme images directory.
 */
define('XHN_IMAGES_DIR', drupal_get_path('theme', 'xhn') . '/images/');

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
 * @throws \Exception
 */
function xhn_preprocess_field(&$variables) {
  switch ($variables['element']['#field_name']) {
    case 'field_gold_cost':
      $variables['label'] = theme('image', ['path' => XHN_IMAGES_DIR . 'gold.png']);
      break;

    case 'field_tree_cost':
      $variables['label'] = theme('image', ['path' => XHN_IMAGES_DIR . 'tree.png']);
      break;

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
      '#markup' => theme('image', ['path' => XHN_IMAGES_DIR . 'empty.jpg']),
    ];
  }

  // Save themed calculator's images to variable.
  $vars['items'] = $items;

  // Preprocess calculated "fields".
  if ($vars['calculated_fields']) {
    foreach ($vars['calculated_fields'] as $field_name => $item) {
      if ($item['value'] > 0 || $item['value'] != '') {
        // Change labels. Set images instead of text.
        switch ($field_name) {
          case 'field_gold_cost':
            $item['label'] = theme('image', ['path' => XHN_IMAGES_DIR . 'gold.png']);
            break;

          case 'field_tree_cost':
            $item['label'] = theme('image', ['path' => XHN_IMAGES_DIR . 'tree.png']);
            break;
        }
        // Create items with label and value for render in template.
        $vars['calculated_fields'][$field_name] = [
          '#type' => 'item',
          '#title' => $item['label'],
          // Use list for text fields, it does not affect on numeric fields.
          '#markup' => '<ul>' . $item['value'] . $item['suffix'] . '</ul>',
        ];
      }
      else {
        // If value not greater than 0 - remove unnecessary display of field.
        unset($vars['calculated_fields'][$field_name]);
      }
    }
  }
  else {
    // Prevent notice.
    $vars['calculated_fields'] = [];
  }
}
