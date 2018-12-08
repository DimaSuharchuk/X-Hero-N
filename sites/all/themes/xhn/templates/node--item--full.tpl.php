<article class="<?php print $classes; ?>"<?php print $attributes; ?>>

  <?php print render($title_prefix); ?>
  <?php if (!$page): ?>
      <h2<?php print $title_attributes; ?>>
          <a href="<?php print $node_url; ?>"><?php print $title; ?></a></h2>
  <?php endif; ?>
  <?php print render($title_suffix); ?>

  <?php if ($display_submitted): ?>
      <div class="posted">
        <?php if ($user_picture): ?>
          <?php print $user_picture; ?>
        <?php endif; ?>
        <?php print $submitted; ?>
      </div>
  <?php endif; ?>

  <?php
  // We hide the comments and links now so that we can render them later.
  hide($content['comments']);
  hide($content['links']);
  hide($content['field_tags']);
  ?>

    <div class="row">
        <div class="small-4 medium-2 large-1 columns">
          <?php print render($content['field_icon']); ?>
        </div>
        <div class="small-8 medium-10 large-11 columns">
          <?php print render($content['field_description']); ?>
        </div>
    </div>

  <?php print render($content); ?>

  <?php if (!empty($content['field_tags']) && !$is_front): ?>
    <?php print render($content['field_tags']) ?>
  <?php endif; ?>

  <?php print render($content['comments']); ?>

</article>
