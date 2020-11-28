SUBDIRS = libgde2-desktop man docs po schemas tools icons

if GDE2_ABOUT_ENABLED
SUBDIRS += gde2-about
endif

ACLOCAL_AMFLAGS = -I m4 ${ACLOCAL_FLAGS}

DISTCHECK_CONFIGURE_FLAGS = \
	--enable-gtk-doc \
	--enable-mpaste \
	--with-gtk=$(GTK_API_VERSION)

if GDE2_ABOUT_ENABLED
versiondir = $(datadir)/gde2-about
version_DATA = gde2-version.xml
endif

@INTLTOOL_XML_RULE@

EXTRA_DIST =			\
	autogen.sh		\
	COPYING-DOCS		\
	gde2-version.xml.in.in

CLEANFILES = \
	$(version_DATA)

MAINTAINERCLEANFILES = \
	$(srcdir)/aclocal.m4 \
	$(srcdir)/config.guess \
	$(srcdir)/config.h.in \
	$(srcdir)/config.sub \
	$(srcdir)/depcomp \
	$(srcdir)/install-sh \
	$(srcdir)/ltmain.sh \
	$(srcdir)/missing \
	$(srcdir)/mkinstalldirs \
	`find "$(srcdir)" -type f -name Makefile.in -print` \
	$(srcdir)/configure \
	$(srcdir)/gtk-doc.make \
	$(srcdir)/m4/gtk-doc.m4 \
	$(srcdir)/m4/intltool.m4

# Build ChangeLog from GIT  history
ChangeLog:
	$(AM_V_GEN) if test -d $(top_srcdir)/.git; then \
		GIT_DIR="$(top_srcdir)/.git" git log --stat > $@; \
	fi

dist: ChangeLog

.PHONY: ChangeLog

-include $(top_srcdir)/git.mk
