<section class="<?php print $classes; ?> small-12 medium-4 columns">

  <?php if ($block->subject): ?>
      <h2<?php print $title_attributes; ?>><?php print $block->subject ?></h2>
  <?php endif; ?>

    <div class="block-content" id="block-calculator">
      <?php print $content ?>
    </div>

</section>
