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
          'weight' => '4',
        ),
        'description' => array(
          'weight' => '5',
        ),
        'gold_cost' => array(
          'weight' => '7',
        ),
        'tree_cost' => array(
          'weight' => '8',
        ),
        'strength' => array(
          'weight' => '9',
        ),
        'agility' => array(
          'weight' => '10',
        ),
        'intelligence' => array(
          'weight' => '11',
        ),
        'attack' => array(
          'weight' => '12',
        ),
        'defense' => array(
          'weight' => '13',
        ),
        'health' => array(
          'weight' => '14',
        ),
        'lifesteal' => array(
          'weight' => '16',
        ),
        'health_regen_units' => array(
          'weight' => '17',
        ),
        'health_regen_percent' => array(
          'weight' => '18',
        ),
        'mana_regen_units' => array(
          'weight' => '19',
        ),
        'mana_regen_percent' => array(
          'weight' => '20',
        ),
        'attack_speed' => array(
          'weight' => '21',
        ),
        'critical' => array(
          'weight' => '22',
        ),
        'dodge' => array(
          'weight' => '23',
        ),
        'move_speed' => array(
          'weight' => '24',
        ),
        'passive' => array(
          'weight' => '25',
        ),
        'active' => array(
          'weight' => '26',
        ),
        'category' => array(
          'weight' => '0',
        ),
        'weight_in_shop' => array(
          'weight' => '3',
        ),
        'mana' => array(
          'weight' => '15',
        ),
        'boss' => array(
          'weight' => '1',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_item__item'] = $strongarm;

  return $export;
}
