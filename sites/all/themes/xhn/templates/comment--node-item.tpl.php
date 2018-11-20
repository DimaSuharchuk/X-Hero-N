<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>

  <div class="attribution">

    <?php print $picture; ?>

    <div class="submitted">
      <p class="commenter-name">
        <?php print $variables['comment']->name; ?>
      </p>
      <p class="comment-time">
        <?php print $created; ?>
      </p>
    </div>
  </div>

  <div class="comment-text">

    <div class="content"<?php print $content_attributes; ?>>
      <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['links']);
      print render($content);
      ?>
      <?php if ($signature): ?>
        <div class="user-signature clearfix">
          <?php print $signature; ?>
        </div>
      <?php endif; ?>
    </div>

    <?php print render($content['links']); ?>
  </div>
</div>
