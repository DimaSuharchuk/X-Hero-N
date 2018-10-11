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
        'category' => array(
          'weight' => '0',
        ),
        'name' => array(
          'weight' => '1',
        ),
        'description' => array(
          'weight' => '2',
        ),
        'gold_cost' => array(
          'weight' => '3',
        ),
        'tree_cost' => array(
          'weight' => '4',
        ),
        'strength' => array(
          'weight' => '5',
        ),
        'agility' => array(
          'weight' => '6',
        ),
        'intelligence' => array(
          'weight' => '7',
        ),
        'attack' => array(
          'weight' => '8',
        ),
        'defense' => array(
          'weight' => '9',
        ),
        'health' => array(
          'weight' => '10',
        ),
        'lifesteal' => array(
          'weight' => '11',
        ),
        'health_regen_units' => array(
          'weight' => '12',
        ),
        'health_regen_percent' => array(
          'weight' => '13',
        ),
        'mana_regen_units' => array(
          'weight' => '14',
        ),
        'mana_regen_percent' => array(
          'weight' => '15',
        ),
        'attack_speed' => array(
          'weight' => '16',
        ),
        'critical' => array(
          'weight' => '17',
        ),
        'dodge' => array(
          'weight' => '18',
        ),
        'move_speed' => array(
          'weight' => '19',
        ),
        'passive' => array(
          'weight' => '20',
        ),
        'active' => array(
          'weight' => '21',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_item__item'] = $strongarm;

  return $export;
}
