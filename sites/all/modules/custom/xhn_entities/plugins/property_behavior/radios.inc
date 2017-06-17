<?php

$plugin = [
  'label' => t('Radios'),
  'default_widget' => 'xhn_entities_radios_property_entity_widget',
  'default_formatter' => 'xhn_entities_radios_property_entity_formatter',
];

/**
 * Display field in edit form.
 */
function xhn_entities_radios_property_entity_widget($property, $variables) {
  $bundle = $variables['entity']->type;

  $widget = [
    '#type' => 'radios',
    '#title' => $variables['properties'][$property]['label'],
    '#options' => [],
  ];

  foreach (module_implements('entity_property_widget_alter') as $module) {
    $function = $module . '_entity_property_widget_alter';
    $widget = $function($widget, $bundle, $property);
  }

  $widget['#default_value'] = !empty($variables['entity']->{$property}) ? $variables['entity']->{$property} : current($widget['#options']);

  return $widget;
}

/**
 * Display the property value on entity view.
 */
function xhn_entities_radios_property_entity_formatter($property, $variables) {
  $element = [];
  $value = !empty($variables['entity']->{$property}) ? $variables['entity']->{$property} : '';

  if (!empty($value)) {
    $element = [
      '#type' => 'item',
      '#title' => $property,
      '#markup' => $value,
    ];
  }

  return $element;
}
