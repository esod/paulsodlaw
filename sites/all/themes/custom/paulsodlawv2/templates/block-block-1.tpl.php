<?php
// $Id: block.tpl.php,v 1.3 2007/08/07 08:39:36 goba Exp $
?>
<div id="block-<?php print $block->module .'-'. $block->delta; ?>" class="clear-block block block-<?php print $block->module ?>">

<?php if (!empty($block->subject)): ?>

  <h2 class="title" title="Directions to our office"><a href="office-location"><?php print $block->subject ?></a></h2>
<?php endif;?>

  <div class="content"><?php print $block->content ?></div>

</div>
