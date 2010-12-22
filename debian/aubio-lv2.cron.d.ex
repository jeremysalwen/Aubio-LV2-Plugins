#
# Regular cron jobs for the aubio-lv2 package
#
0 4	* * *	root	[ -x /usr/bin/aubio-lv2_maintenance ] && /usr/bin/aubio-lv2_maintenance
