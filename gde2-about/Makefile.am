bin_PROGRAMS = gde2-about
gde2_about_SOURCES = gde2-about.c gde2-about.h
gde2_about_CFLAGS = $(GDE2_ABOUT_CFLAGS) $(UNIQUE_CFLAGS)
gde2_about_LDADD = $(GDE2_ABOUT_LIBS) $(UNIQUE_LIBS) $(top_builddir)/libgde2-desktop/libgde2-desktop-2.la

AM_CPPFLAGS = \
	-I$(top_srcdir) \
	$(GDE2_ABOUT_CFLAGS) \
	-DLOCALE_DIR=\"$(datadir)/locale\" \
	-DPIXMAPS_DIR=\"$(datadir)/pixmaps/\"

@INTLTOOL_DESKTOP_RULE@

desktopdir = $(datadir)/applications
desktop_in_files = gde2-about.desktop.in
desktop_DATA = $(desktop_in_files:.desktop.in=.desktop)

CLEANFILES = gde2-about.desktop gde2-about

#-include $(top_srcdir)/git.mk

