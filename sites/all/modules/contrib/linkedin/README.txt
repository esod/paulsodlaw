=== LINKEDIN INTEGRATION ===

Maintainers:  Pascal Morin (bellesmanieres)
              Greg Harvey (greg.harvey)

Original code written by Pascal Morin and sponsored by CMS Professionals
on behalf of Economist Conferences.

Dependencies:
============

This module requires the OAuth module:
http://drupal.org/project/oauth

Installation:
============

Once you have downloaded the OAuth and LinkedIn modules to your modules
directories, install this module in the usual way.

Configuration:
=============

You will need to apply for an API key from LinkedIn:
http://developer.linkedin.com

Note, the URL you provide when you create your API keys *must* match
the URL of your server - this means you'll need a separate key for each
stage or development server.

Once you have your API credentials, you can enter them at:
admin/settings/linkedin

On that settings page you can also determine which content types are
postable to LinkedIn and also globally enable or disable LinkedIn
profile synchronisation support.

There are new permissions available on the user permissions page. Do
not forget to review and configure them:
admin/user/permissions

If correctly permissioned, users will be able to connect their Drupal
user account to their LinkedIn account via OAuth from the user edit
page. There is an additional LinkedIn tab when editing a user:
user/%uid/edit/linkedin

Users click the button, are taken to http://www.linkedin.com for
authorisation and are then returned to Drupal. At this point they
are presented with options, depending on what they are permitted to
do with the LinkedIn API.

Troubleshooting:
=============
Carefully check the following :
- Server time : an out of sync server will issue a wrong timestamp. Linkedin.com requires that the timestamp must be within 5 minutes of accurate
- Integration url : integration url you gave at https://www.linkedin.com/secure/developer is the actual one from wich you are issuing request
- Callback URL : do not specifiy a callback url at https://www.linkedin.com/secure/developer

Also, be sure to check the watchdog logs for more infos on the error.