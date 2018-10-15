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
          'weight' => '3',
        ),
        'description' => array(
          'weight' => '5',
        ),
        'gold_cost' => array(
          'weight' => '6',
        ),
        'tree_cost' => array(
          'weight' => '7',
        ),
        'strength' => array(
          'weight' => '8',
        ),
        'agility' => array(
          'weight' => '9',
        ),
        'intelligence' => array(
          'weight' => '10',
        ),
        'attack' => array(
          'weight' => '11',
        ),
        'defense' => array(
          'weight' => '12',
        ),
        'health' => array(
          'weight' => '13',
        ),
        'lifesteal' => array(
          'weight' => '15',
        ),
        'health_regen_units' => array(
          'weight' => '16',
        ),
        'health_regen_percent' => array(
          'weight' => '17',
        ),
        'mana_regen_units' => array(
          'weight' => '18',
        ),
        'mana_regen_percent' => array(
          'weight' => '19',
        ),
        'attack_speed' => array(
          'weight' => '20',
        ),
        'critical' => array(
          'weight' => '21',
        ),
        'dodge' => array(
          'weight' => '22',
        ),
        'move_speed' => array(
          'weight' => '23',
        ),
        'passive' => array(
          'weight' => '24',
        ),
        'active' => array(
          'weight' => '25',
        ),
        'category' => array(
          'weight' => '0',
        ),
        'weight_in_shop' => array(
          'weight' => '2',
        ),
        'mana' => array(
          'weight' => '14',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_item__item'] = $strongarm;

  return $export;
}
