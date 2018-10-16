<?php
/**
 * @file
 * xhn_eck_item.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function xhn_eck_item_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_eck_bundle_info().
 */
function xhn_eck_item_eck_bundle_info() {
  $items = array(
    'item_item' => array(
      'machine_name' => 'item_item',
      'entity_type' => 'item',
      'name' => 'item',
      'label' => 'Item',
      'config' => array(
        'managed_properties' => array(
          'name' => 'name',
          'tree_cost' => 'tree_cost',
          'gold_cost' => 'gold_cost',
          'agility' => 'agility',
          'strength' => 'strength',
          'intelligence' => 'intelligence',
          'attack' => 'attack',
          'defense' => 'defense',
          'health' => 'health',
          'lifesteal' => 'lifesteal',
          'health_regen_units' => 'health_regen_units',
          'health_regen_percent' => 'health_regen_percent',
          'mana_regen_units' => 'mana_regen_units',
          'mana_regen_percent' => 'mana_regen_percent',
          'dodge' => 'dodge',
          'critical' => 'critical',
          'attack_speed' => 'attack_speed',
          'move_speed' => 'move_speed',
          'passive' => 'passive',
          'active' => 'active',
          'category' => 'category',
          'weight_in_shop' => 'weight_in_shop',
          'mana' => 'mana',
        ),
      ),
    ),
  );
  return $items;
}

/**
 * Implements hook_eck_entity_type_info().
 */
function xhn_eck_item_eck_entity_type_info() {
  $items = array(
    'item' => array(
      'name' => 'item',
      'label' => 'Item',
      'properties' => array(
        'name' => array(
          'label' => 'Название',
          'type' => 'text',
          'behavior' => 'textfield',
        ),
        'tree_cost' => array(
          'label' => 'Дерево',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'gold_cost' => array(
          'label' => 'Золото',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'agility' => array(
          'label' => 'Ловкость',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'strength' => array(
          'label' => 'Сила',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'intelligence' => array(
          'label' => 'Разум',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'attack' => array(
          'label' => 'Атака',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'defense' => array(
          'label' => 'Защита',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'health' => array(
          'label' => 'Здоровье',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'lifesteal' => array(
          'label' => 'Вампиризм',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'health_regen_units' => array(
          'label' => 'Регенерация здоровья, ед',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'health_regen_percent' => array(
          'label' => 'Регенерация здоровья, %',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'mana_regen_units' => array(
          'label' => 'Регенерация маны, ед',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'mana_regen_percent' => array(
          'label' => 'Регенерация маны, %',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'dodge' => array(
          'label' => 'Уворот',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'critical' => array(
          'label' => 'Критический урон 3х',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'attack_speed' => array(
          'label' => 'Скорость атаки',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'move_speed' => array(
          'label' => 'Скорость перемещения',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
        'passive' => array(
          'label' => 'Пассивные способности',
          'type' => 'long_text',
          'behavior' => 'long_text',
        ),
        'active' => array(
          'label' => 'Активные способности',
          'type' => 'long_text',
          'behavior' => 'long_text',
        ),
        'category' => array(
          'label' => 'Категория',
          'type' => 'text',
          'behavior' => 'select',
        ),
        'weight_in_shop' => array(
          'label' => 'Вес в магазине',
          'type' => 'integer',
          'behavior' => 'select',
        ),
        'mana' => array(
          'label' => 'Мана',
          'type' => 'integer',
          'behavior' => 'integer',
        ),
      ),
    ),
  );
  return $items;
}
