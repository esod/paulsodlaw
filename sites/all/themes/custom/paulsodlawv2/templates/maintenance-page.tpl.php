<?php
// $Id: maintenance-page.tpl.php,v 1.17 2009/11/04 20:49:23 johnalbin Exp $

/**
 * @file maintenance-page.tpl.php
 *
 * Theme implementation to display a single Drupal page while off-line.
 *
 * All the available variables are mirrored in page.tpl.php. Some may be left
 * blank but they are provided for consistency.
 *
 *
 * @see template_preprocess()
 * @see template_preprocess_maintenance_page()
 */
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Strict//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" lang="<?php print $language->language; ?>" dir="<?php print $language->dir; ?>">

<head>
  <title><?php print $head_title; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $classes; ?>">

  <div id="page-wrapper"><div id="page">

    <div id="header"><div class="section clearfix">

      <?php if ($logo): ?>
        <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home" id="logo"><img src="<?php print $logo; ?>" alt="<?php print t('Home'); ?>" /></a>
      <?php endif; ?>

      <?php if ($site_name || $site_slogan): ?>
        <div id="name-and-slogan">
          <?php if ($site_name): ?>
            <div id="site-name"><strong>
              <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home">
              <?php print $site_name; ?>
              </a>
            </strong></div>
          <?php endif; ?>
          <?php if ($site_slogan): ?>
            <div id="site-slogan"><?php print $site_slogan; ?></div>
          <?php endif; ?>
        </div> <!-- /#name-and-slogan -->
      <?php endif; ?>

      <?php print $header; ?>

    </div></div> <!-- /.section, /#header -->

    <div id="maintenance-main-wrapper"><div id="maintenance-main" class="clearfix<?php if ($navigation) { print ' with-navigation'; } ?>">

      <div id="content" class="column"><div class="maintenance-section">

        <?php print $highlight; ?>

        <?php if ($title): ?>
          <h1 class="maintenance-title"><?php print $title; ?></h1>
        <?php endif; ?>
        <?php if ($messages): print $messages; endif; ?>

        <?php print $content_top; ?>

        <div id="maintenance-content-area">
          <?php print $content; ?>
        </div>

        <?php print $content_bottom; ?>

      </div></div> <!-- /.section, /#content -->

      <?php if ($navigation): ?>
        <div id="navigation"><div class="section clearfix">

          <?php print $navigation; ?>

        </div></div> <!-- /.section, /#navigation -->
      <?php endif; ?>

      <?php print $sidebar_first; ?>

      <?php print $sidebar_second; ?>

    </div></div> <!-- /#main, /#main-wrapper -->

    <div id="footer"><div id="maintenance-footer-wrapper">
    <div id="maintenance-directions">
      <a href="mailto:paul.sod@paulsodlaw.com">Email our office</a>&emsp;|&emsp;<a href="http://www.linkedin.com/pub/paul-sod/21/179/9ab" target="_blank" class="linkedin-logo" title="Follow me on LinkedIn">Linkedin</a></li>
    </div></div></div> <!-- /#footer, /#maintenance-footer-wrapper, /#maintenance-directions -->

        <div class="disclaimer">Copyright © 2011 The Offices of Paul Sod Law</div>
    
  </div></div> <!-- /#page, /#page-wrapper -->

  <?php print $page_closure; ?>

  <?php print $closure; ?>

</body>
</html>
