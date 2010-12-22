## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(prefix)/$(DATADIRNAME)/locale"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(datadir)"\" $(AUBIOLV2_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = libaubiolv2.la


libaubiolv2_la_SOURCES = \
	lib.c           \
	tss-plugin.c           \
	tss-plugin.h           \
	aubiolv2.h

libaubiolv2_la_LDFLAGS = 

libaubiolv2_la_LIBADD = $(AUBIOLV2_LIBS)

include_HEADERS = 

install-data-hook:
	$(INSTALL) -d -m 755 $(DESTDIR)$(with_lv2_dir)/aubio.lv2
	$(INSTALL) -c -m 755 $(top_builddir)/src/.libs/libaubiolv2.so $(DESTDIR)$(with_lv2_dir)aubio.lv2/libaubiolv2.so
	rm -f $(DESTDIR)$(with_lv2_dir)/aubio.lv2/*.ttl
	$(INSTALL) -c -m 775 $(top_builddir)/src/*.ttl -p $(DESTDIR)$(with_lv2_dir)/aubio.lv2/
uninstall-hook:
	rm -f $(DESTDIR)$(with_lv2_dir)/aubio.lv2/libaubiolv2.so
	rm -f $(DESTDIR)$(with_lv2_dir)/aubio.lv2/*.ttl
	rmdir -p $(DESTDIR)$(with_lv2_dir)/aubio.lv2 || true
