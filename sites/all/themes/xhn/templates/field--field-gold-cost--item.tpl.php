<?php
$args = arg();
if (is_numeric($args[1])) {
  $node = node_load($args[1]);
  // Show this label for "Boss items".
  if (!empty($node->field_boss) && $node->field_boss[LANGUAGE_NONE][0]['value']) : ?>
      <div>
          <strong>Цена продажи:</strong>
      </div>
  <?php endif;
} ?>

<div class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if (!$label_hidden): ?>
      <div class="field-label"<?php print $title_attributes; ?>><?php print $label ?>
          :&nbsp;
      </div>
  <?php endif; ?>
    <div class="field-items"<?php print $content_attributes; ?>>
      <?php foreach ($items as $delta => $item): ?>
          <div class="field-item <?php print $delta % 2 ? 'odd' : 'even'; ?>"<?php print $item_attributes[$delta]; ?>><?php print render($item); ?></div>
      <?php endforeach; ?>
    </div>
</div>