<?php

$plugin = [
  'label' => t('Text'),
  'default_widget' => 'xhn_entities_text_property_entity_widget',
  'default_formatter' => 'xhn_entities_text_property_entity_formatter',
];

/**
 * Display field in edit form.
 */
function xhn_entities_text_property_entity_widget($property, $variables) {
  $bundle = $variables['entity']->type;

  $widget = [
    '#type' => 'textfield',
    '#title' => $variables['properties'][$property]['label'],
  ];

  foreach (module_implements('entity_property_widget_alter') as $module) {
    $function = $module . '_entity_property_widget_alter';
    $widget = $function($widget, $bundle, $property);
  }

  $widget['#default_value'] = _xhn_entities_text_property_extract($variables['entity'], $property);

  return $widget;
}

/**
 * Display the property value on entity view.
 */
function xhn_entities_text_property_entity_formatter($property, $variables) {
  $element = [];
  $value = _xhn_entities_text_property_extract($variables['entity'], $property);

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
function _xhn_entities_text_property_extract($entity, $property) {
  return isset($entity->{$property}) ? $entity->{$property} : '';
}
