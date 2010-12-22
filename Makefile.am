## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS = src 

aubiolv2docdir = ${prefix}/doc/aubiolv2
aubiolv2doc_DATA = \
	README\
	COPYING\
	AUTHORS\
	INSTALL


EXTRA_DIST = $(aubiolv2doc_DATA)


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(aubiolv2docdir)
