<?php if (!empty($used_for)): ?>
    <h6 class="text-center">Используется для</h6>
    <hr>
    <div class="used-for-items inline-items">
      <?php print render($used_for); ?>
    </div>
<?php endif; ?>

<div class="target-node inline-items">
    <a href="<?php print drupal_get_path_alias("node/{$nid}"); ?>">
      <?php print render($target_node); ?>
    </a>
</div>

<?php if (!empty($requires)): ?>
    <div class="require-items inline-items">
      <?php print render($requires); ?>
    </div>
    <hr>
    <h6 class="text-center">Для сборки потребуется</h6>
<?php endif; ?>
