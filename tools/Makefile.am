bin_PROGRAMS = gde2-color-select
bin_SCRIPTS =

AM_CPPFLAGS = \
	-I$(top_srcdir)

gde2_color_select_SOURCES = \
	gde2-color-select.c

gde2_color_select_CFLAGS = \
	-DLOCALE_DIR=\"$(datadir)/locale\" \
	$(GDE2_DESKTOP_CFLAGS)

gde2_color_select_LDADD = \
	$(top_builddir)/libgde2-desktop/libgde2-desktop-2.la \
	$(GDE2_DESKTOP_LIBS)

@INTLTOOL_DESKTOP_RULE@

desktopdir = $(datadir)/applications
desktop_in_files = gde2-color-select.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

if MPASTE_ENABLED
bin_SCRIPTS += mpaste
endif

EXTRA_DIST = \
	mpaste

CLEANFILES = *.desktop *.desktop.in
