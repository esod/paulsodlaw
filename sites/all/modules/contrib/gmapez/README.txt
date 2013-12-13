Drupal GMapez integration by Berend de Boer <berend@pobox.com>.

Documentation on GMapez on the GMapez site:

  http://n01se.net/gmapez/start.html

The default gmapez script allows putting marker on the map if you know
the latitude and longitude:

  <div class="GMapEZ" style="width: 300px; height: 300px;">
    <a href="http://maps.google.com/maps?ll=41.092104,-85.144740&amp;spn=0.006130,0.009795&amp;t=k&amp;hl=en">
    </a>
  </div>

For this to work, you will need to do two things:

1. Set the input format to full HTML.

2. Make sure the line break filter in full HTML is turned off. If you
   copy/paste examples from the GMapEZ site, the Drupal filter will
   insert line breaks at very inconvenient places. The result will be
   that your map is not shown, you will only see the controls or the
   Google logo.

In addition the improved gmapez script allows you to use street names,
instead of latitude and longitude with:

  <div class="GMapEZ GSmallMapControl" style="width: 600px; height: 480px;"><a href="http://maps.google.com/maps?q=Victoria%20Street%20East,%20Auckland,%20NZ"></a></div>

GMapez can always be enabled or it can be enabled programmatically
from within a Drupal module by calling:

  gmapez_add_script();

And emitting a piece of HTML that contains the GMapez div.
