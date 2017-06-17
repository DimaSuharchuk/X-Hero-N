<?php

$plugin = [
  'label' => t('Select'),
  'default_widget' => 'xhn_entities_select_property_entity_widget',
  'default_formatter' => 'xhn_entities_select_property_entity_formatter',
];

/**
 * Display field in edit form.
 */
function xhn_entities_select_property_entity_widget($property, $variables) {
  $bundle = $variables['entity']->type;

  $widget = [
    '#type' => 'select',
    '#title' => $variables['properties'][$property]['label'],
    '#options' => [],
    '#multiple' => FALSE,
    '#default_value' => _xhn_entities_select_property_extract($variables['entity'], $property),
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
function xhn_entities_select_property_entity_formatter($property, $variables) {
  $element = [];
  $value = _xhn_entities_select_property_extract($variables['entity'], $property);

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
function _xhn_entities_select_property_extract($entity, $property) {
  if (empty($entity->{$property})) {
    return '';
  }
  if (@unserialize($entity->{$property})) {
    return unserialize($entity->{$property});
  }

  return $entity->{$property};
}
