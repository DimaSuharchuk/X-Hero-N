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
