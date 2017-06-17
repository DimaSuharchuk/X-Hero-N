<?php
/**
 * @file
 * define ECK Property plugin for a date property with following
 *       - Date only without time
 *       - Presented in DB as Text formatted: Y-m-d
 *       - Loaded into entity as Text also with format: Y-m-d
 */

$plugin = [
  'label' => t('Date only text'),
  'default_widget' => 'xhn_entities_date_only_text_property_entity_widget',
  'default_formatter' => 'xhn_entities_date_only_text_property_entity_formatter',
  'entity_save' => 'xhn_entities_date_only_text_property_entity_save',
];

/**
 * Display field in edit form.
 */
function xhn_entities_date_only_text_property_entity_widget($property, $variables) {
  $bundle = $variables['entity']->type;

  $widget = [
    '#type' => 'textfield',
    '#title' => t($variables['properties'][$property]['label']),
    '#maxlength' => 12,
    '#attributes' => ['class' => ['eck-date-only-text']],
    '#default_value' => _xhn_entities_date_only_text_property_extract($variables['entity'], $property),
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
function xhn_entities_date_only_text_property_entity_formatter($property, $variables) {
  $element = [
    '#type' => 'item',
    '#title' => $property,
    '#markup' => _xhn_entities_date_only_text_property_extract($variables['entity'], $property),
  ];

  return $element;
}

/**
 * Save as date only text.
 */
function xhn_entities_date_only_text_property_entity_save($property, $vars) {
  $vars['entity']->{$property} = _xhn_entities_date_only_text_property_extract($vars['entity'], $property);
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
function _xhn_entities_date_only_text_property_extract($entity, $property) {
  $value = empty($entity->{$property}) ? '' : $entity->{$property};
  if (is_numeric($value)) {
    $value = date('Y-m-d', $value);
  }
  return $value;
}
