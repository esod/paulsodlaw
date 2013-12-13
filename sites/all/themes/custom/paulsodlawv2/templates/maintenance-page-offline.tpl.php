<?php
// $Id: maintenance-page-offline.tpl.php $

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
  <title><?php print 'Site off-line | www.paulsodlaw.com'; ?></title>
  <?php print $head; ?>
  <?php print $styles; ?>
  <?php print $scripts; ?>
</head>
<body class="<?php print $classes; ?>">

  <div id="page-wrapper"><div id="page">

    <div id="header"><div class="section clearfix">


        <div id="name-and-slogan">
            <div id="maintenance-site-name"><strong>
              <a href="<?php print $base_path; ?>" title="<?php print t('Home'); ?>" rel="home">
              <?php print 'Law Offices of Paul M. Sod'; ?>
              </a>
            </strong></div>
            <div id="site-slogan"><?php print 'Established 1990<br />Intelligence, Experience, and Integrity'; ?></div>
        </div> <!-- /#name-and-slogan -->

      <?php print $header; ?>

    </div></div> <!-- /.section, /#header -->

    <div id="maintenance-main-wrapper"><div id="maintenance-main" class="clearfix<?php if ($navigation) { print ' with-navigation'; } ?>">

      <div id="maintenance-content" class="column"><div class="maintenance-section">

        <?php if ($title): ?>
          <h1 class="maintenance-title"><?php print $title; ?></h1>
        <?php endif; ?>

        <div id="maintenance-content-area">
          <?php print $content; ?>
        </div>

      </div></div> <!-- /.section, /#content -->

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
