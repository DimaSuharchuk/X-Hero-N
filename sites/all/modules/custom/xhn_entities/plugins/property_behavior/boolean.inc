<?php

$plugin = [
  'label' => t('Boolean'),
  'default_widget' => 'xhn_entities_boolean_property_entity_widget',
  'default_formatter' => 'xhn_entities_boolean_property_entity_formatter',
];

/**
 * Display field in edit form.
 */
function xhn_entities_boolean_property_entity_widget($property, $variables) {
  $bundle = $variables['entity']->type;

  $widget = [
    '#type' => 'checkbox',
    '#title' => $variables['properties'][$property]['label'],
    '#default_value' => _xhn_entities_boolean_property_extract($variables['entity'], $property),
  ];

  foreach (module_implements('entity_property_widget_alter') as $module) {
    $function = $module . '_entity_property_widget_alter';
    $widget = $function($widget, $bundle, $property);
  }

  return $widget;
}

/**
 * Display the property value on entity view.
 */
function xhn_entities_boolean_property_entity_formatter($property, $variables) {
  $element = [];
  $value = _xhn_entities_boolean_property_extract($variables['entity'], $property);

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
function _xhn_entities_boolean_property_extract($entity, $property) {
  return isset($entity->{$property}) ? $entity->{$property} : FALSE;
}
