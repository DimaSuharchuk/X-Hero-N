<?php

$plugin = [
  'label' => t('Exact date'),
  'default_widget' => 'xhn_entities_exact_date_property_entity_widget',
  'default_formatter' => 'xhn_entities_exact_date_property_entity_formatter',
  'entity_save' => 'xhn_entities_exact_date_property_entity_save',
];

/**
 * Display field in edit form.
 */
function xhn_entities_exact_date_property_entity_widget($property, $variables) {
  $bundle = $variables['entity']->type;

  $widget = [
    '#type' => 'date_popup',
    '#title' => $variables['properties'][$property]['label'],
    '#date_format' => 'd-m-Y H:i',
    '#date_year_range' => '-10:0',
  ];

  foreach (module_implements('entity_property_widget_alter') as $module) {
    $function = $module . '_entity_property_widget_alter';
    $widget = $function($widget, $bundle, $property);
  }

  $widget['#default_value'] = '';
  if (!empty($variables['entity']->{$property})) {
    $widget['#default_value'] = date('Y-m-d H:i', $variables['entity']->{$property});
  }

  return $widget;
}

/**
 * Display the property value on entity view.
 */
function xhn_entities_exact_date_property_entity_formatter($property, $variables) {
  $element = [];
  $value = _xhn_entities_exact_date_property_extract($variables['entity'], $property);

  if (!empty($value)) {
    $element = [
      '#type' => 'item',
      '#title' => $property,
      '#markup' => $value,
    ];
  }

  return $element;
}

/**
 * Save date as timestamp.
 */
function xhn_entities_exact_date_property_entity_save($property, $vars) {
  $date = &$vars['entity']->{$property};
  if (is_string($date)) {
    $date = strtotime($date);
  }
}

/**
 * Helper function that gets the property from an entity.
 *
 * @param object $entity
 *   An entity object.
 * @param string $property
 *   The name of the property that contains the value.
 *
 * @return string
 *   The value of the property.
 */
function _xhn_entities_exact_date_property_extract($entity, $property) {
  return !empty($entity->{$property}) ? date('d-m-Y H:i', $entity->{$property}) : '';
}
