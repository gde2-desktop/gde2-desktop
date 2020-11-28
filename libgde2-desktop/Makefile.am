libgde2_desktopdir = $(includedir)/gde2-desktop-2.0/libgde2-desktop
libgde2_desktop_HEADERS = \
	gde2-desktop.h \
	gde2-desktop-utils.h \
	gde2-desktop-item.h \
	gde2-dconf.h \
	gde2-gsettings.h \
	gde2-aboutdialog.h \
	gde2-bg.h			\
	gde2-bg-crossfade.h		\
	gde2-desktop-thumbnail.h	\
	gde2-rr.h			\
	gde2-rr-config.h		\
	gde2-rr-labeler.h \
	gde2-colorbutton.h \
	gde2-colorsel.h \
	gde2-colorseldialog.h

lib_LTLIBRARIES = libgde2-desktop-2.la

AM_CPPFLAGS =							\
	$(GDE2_DESKTOP_CFLAGS)					\
	$(XLIB_CFLAGS)						\
	$(DCONF_CFLAGS)						\
	-DG_LOG_DOMAIN=\"Gde2Desktop\"				\
	-DGDE2LOCALEDIR=\""$(prefix)/$(DATADIRNAME)/locale\""	\
	-DPNP_IDS=\""$(PNP_IDS)"\"				\
	$(DISABLE_DEPRECATED_CFLAGS)

AM_CFLAGS = $(WARN_CFLAGS)

noinst_PROGRAMS = test-ditem test

CLEANFILES =

introspection_sources = \
	gde2-desktop-utils.c	\
	gde2-desktop-thumbnail.c \
	gde2-thumbnail-pixbuf-utils.c \
	gde2-dconf.c \
	gde2-gsettings.c \
	gde2-aboutdialog.c \
	gde2-bg.c		\
	gde2-bg-crossfade.c	\
	display-name.c		\
	gde2-rr.c		\
	gde2-rr-config.c	\
	gde2-rr-output-info.c	\
	gde2-rr-labeler.c	\
	gde2-colorbutton.c \
	gde2-colorsel.c \
	gde2-colorseldialog.c \
	edid-parse.c

libgde2_desktop_2_la_SOURCES =		\
	$(introspection_sources)	\
	gde2-desktop-item.c		\
	gde2-rr-private.h		\
	edid.h				\
	private.h

libgde2_desktop_2_la_LIBADD =	\
	$(XLIB_LIBS)		\
	$(GDE2_DESKTOP_LIBS)	\
	$(DCONF_LIBS)

libgde2_desktop_2_la_LDFLAGS = \
	-version-info $(LT_VERSION) \
	-export-symbols-regex "^gde2_.*" \
	-no-undefined

test_SOURCES = \
	test.c

test_LDADD = \
	libgde2-desktop-2.la		\
	$(GDE2_DESKTOP_LIBS)

test_ditem_SOURCES = \
	test-ditem.c

test_ditem_LDADD = \
	libgde2-desktop-2.la		\
	$(XLIB_LIBS)			\
	$(GDE2_DESKTOP_LIBS)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gde2-desktop-2.0.pc

if USE_INTERNAL_PNP_IDS
pnpdatadir = $(datadir)/libgde2-desktop
pnpdata_DATA = pnp.ids
endif
pnpdata_DATA_dist = pnp.ids

check:
	test -s $(top_srcdir)/libgde2-desktop/pnp.ids

-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = --add-include-path=$(srcdir) --warn-all
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

if HAVE_INTROSPECTION

Gde2Desktop-2.0.gir: libgde2-desktop-2.la
Gde2Desktop_2_0_gir_INCLUDES = GObject-2.0 Gtk-$(GTK_API_VERSION)
Gde2Desktop_2_0_gir_PACKAGES = gdk-pixbuf-2.0 glib-2.0 gobject-2.0 gio-2.0 gtk+-$(GTK_API_VERSION)
Gde2Desktop_2_0_gir_CFLAGS = -DGDE2_DESKTOP_USE_UNSTABLE_API -I$(top_srcdir)
Gde2Desktop_2_0_gir_LIBS = libgde2-desktop-2.la
Gde2Desktop_2_0_gir_FILES = $(introspection_sources) $(libgde2_desktop_HEADERS)
Gde2Desktop_2_0_gir_SCANNERFLAGS = --identifier-prefix=Gde2 --symbol-prefix=gde2_
INTROSPECTION_SCANNER_ARGS += $(patsubst %,--c-include='libgde2-desktop/%',$(libgde2_desktop_HEADERS))
INTROSPECTION_GIRS += Gde2Desktop-2.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES += $(gir_DATA) $(typelib_DATA)
endif

EXTRA_DIST = \
	gde2-desktop-2.0.pc.in                \
	gde2-desktop-2.0-uninstalled.pc.in    \
	$(pnpdata_DATA_dist)

MAINTAINERCLEANFILES = \
	pnp.ids

-include $(top_srcdir)/git.mk
