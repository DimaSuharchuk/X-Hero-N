<div class="inline-items">
  <?php foreach ($items as $key => $item) : ?>
      <div class="item-calculated" id="item-calculated-<?php print $key; ?>"
           data-nid="<?php print isset($item['#node']->nid) ? $item['#node']->nid : ''; ?>">
        <?php print render($item); ?>
      </div>
  <?php endforeach; ?>
</div>

<div class="calculated-fields-wrapper">
  <?php foreach ($calculated_fields as $field) {
    print '<div class="calculated-field-output">' . render($field) . '</div>';
  } ?>
</div>
