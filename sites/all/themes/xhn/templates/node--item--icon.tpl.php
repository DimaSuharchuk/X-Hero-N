<?php
$args = arg();
$is_on_node_view_full = $args[0] == 'node' && is_numeric($args[1]);
if ($is_on_node_view_full) {
  print "<a href='{$attributes_array['about']}'>";
}
?>

<article id="node-<?php print $node->nid; ?>"
         class="<?php print $classes; ?> item-clickable"
         data-nid="<?php print $node->nid; ?>" <?php print $attributes; ?>>

  <?php
  hide($content['comments']);
  hide($content['links']);
  hide($content['field_tags']);
  print render($content);
  ?>

</article>

<?php if ($is_on_node_view_full): ?>
    </a>
<?php endif; ?>
