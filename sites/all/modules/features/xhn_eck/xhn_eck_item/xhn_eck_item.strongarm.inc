<?php
/**
 * @file
 * xhn_eck_item.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function xhn_eck_item_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_item__item';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'name' => array(
          'weight' => '1',
        ),
        'description' => array(
          'weight' => '3',
        ),
        'gold_cost' => array(
          'weight' => '4',
        ),
        'tree_cost' => array(
          'weight' => '5',
        ),
        'strength' => array(
          'weight' => '6',
        ),
        'agility' => array(
          'weight' => '7',
        ),
        'intelligence' => array(
          'weight' => '8',
        ),
        'attack' => array(
          'weight' => '9',
        ),
        'defense' => array(
          'weight' => '10',
        ),
        'health' => array(
          'weight' => '11',
        ),
        'lifesteal' => array(
          'weight' => '12',
        ),
        'health_regen_units' => array(
          'weight' => '13',
        ),
        'health_regen_percent' => array(
          'weight' => '14',
        ),
        'mana_regen_units' => array(
          'weight' => '15',
        ),
        'mana_regen_percent' => array(
          'weight' => '16',
        ),
        'attack_speed' => array(
          'weight' => '17',
        ),
        'critical' => array(
          'weight' => '18',
        ),
        'dodge' => array(
          'weight' => '19',
        ),
        'move_speed' => array(
          'weight' => '20',
        ),
        'passive' => array(
          'weight' => '21',
        ),
        'active' => array(
          'weight' => '22',
        ),
        'category' => array(
          'weight' => '0',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_item__item'] = $strongarm;

  return $export;
}
