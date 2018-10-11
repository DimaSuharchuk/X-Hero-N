<?php

$plugin = [
  'label' => t('Integer'),
  'default_widget' => 'xhn_entities_integer_property_entity_widget',
  'default_formatter' => 'xhn_entities_integer_property_entity_formatter',
  'entity_save' => 'xhn_entities_integer_property_entity_save',
];

/**
 * Display field in edit form.
 */
function xhn_entities_integer_property_entity_widget($property, $variables) {
  $bundle = $variables['entity']->type;

  $widget = [
    '#type' => 'textfield',
    '#title' => $variables['properties'][$property]['label'],
    '#attributes' => [
      ' type' => 'number',
    ],
  ];

  foreach (module_implements('entity_property_widget_alter') as $module) {
    $function = $module . '_entity_property_widget_alter';
    $widget = $function($widget, $bundle, $property);
  }

  if (!empty($variables['entity']->{$property})) {
    $widget['#default_value'] = $variables['entity']->{$property};
  }

  return $widget;
}

/**
 * Display the property value on entity view.
 */
function xhn_entities_integer_property_entity_formatter($property, $variables) {
  $element = [];
  $value = _xhn_entities_integer_property_extract($variables['entity'], $property);

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
 * Prevent sql error.
 *
 * @param $property
 * @param $vars
 */
function xhn_entities_integer_property_entity_save($property, $vars) {
  $var = &$vars['entity']->{$property};
  if (!is_numeric($var)) {
    $var = '';
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
function _xhn_entities_integer_property_extract($entity, $property) {
  return isset($entity->{$property}) ? $entity->{$property} : '';
}
