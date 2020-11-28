/*
 * gde2-thumbnail.h: Utilities for handling thumbnails
 *
 * Copyright (C) 2002 Red Hat, Inc.
 *
 * This file is part of the Mate Library.
 *
 * The Mate Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * The Mate Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with the Mate Library; see the file COPYING.LIB.  If not,
 * write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 * Author: Alexander Larsson <alexl@redhat.com>
 */

#ifndef GDE2_DESKTOP_THUMBNAIL_H
#define GDE2_DESKTOP_THUMBNAIL_H

#ifndef GDE2_DESKTOP_USE_UNSTABLE_API
#error    MateDesktopThumbnail is unstable API. You must define GDE2_DESKTOP_USE_UNSTABLE_API before including gde2-desktop-thumbnail.h
#endif

#include <glib.h>
#include <glib-object.h>
#include <time.h>
#include <gdk-pixbuf/gdk-pixbuf.h>

G_BEGIN_DECLS

typedef enum {
  GDE2_DESKTOP_THUMBNAIL_SIZE_NORMAL,
  GDE2_DESKTOP_THUMBNAIL_SIZE_LARGE
} MateDesktopThumbnailSize;

#define GDE2_DESKTOP_TYPE_THUMBNAIL_FACTORY		(gde2_desktop_thumbnail_factory_get_type ())
#define GDE2_DESKTOP_THUMBNAIL_FACTORY(obj)	(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDE2_DESKTOP_TYPE_THUMBNAIL_FACTORY, MateDesktopThumbnailFactory))
#define GDE2_DESKTOP_THUMBNAIL_FACTORY_CLASS(klass)	(G_TYPE_CHECK_CLASS_CAST ((klass), GDE2_DESKTOP_TYPE_THUMBNAIL_FACTORY, MateDesktopThumbnailFactoryClass))
#define GDE2_DESKTOP_IS_THUMBNAIL_FACTORY(obj)		(G_TYPE_INSTANCE_CHECK_TYPE ((obj), GDE2_DESKTOP_TYPE_THUMBNAIL_FACTORY))
#define GDE2_DESKTOP_IS_THUMBNAIL_FACTORY_CLASS(klass)	(G_TYPE_CLASS_CHECK_CLASS_TYPE ((klass), GDE2_DESKTOP_TYPE_THUMBNAIL_FACTORY))

typedef struct _MateDesktopThumbnailFactory        MateDesktopThumbnailFactory;
typedef struct _MateDesktopThumbnailFactoryClass   MateDesktopThumbnailFactoryClass;
typedef struct _MateDesktopThumbnailFactoryPrivate MateDesktopThumbnailFactoryPrivate;

struct _MateDesktopThumbnailFactory {
	GObject parent;

	MateDesktopThumbnailFactoryPrivate *priv;
};

struct _MateDesktopThumbnailFactoryClass {
	GObjectClass parent;
};

GType                  gde2_desktop_thumbnail_factory_get_type (void);
MateDesktopThumbnailFactory *gde2_desktop_thumbnail_factory_new      (MateDesktopThumbnailSize     size);

char *                 gde2_desktop_thumbnail_factory_lookup   (MateDesktopThumbnailFactory *factory,
								 const char            *uri,
								 time_t                 mtime);

gboolean               gde2_desktop_thumbnail_factory_has_valid_failed_thumbnail (MateDesktopThumbnailFactory *factory,
										   const char            *uri,
										   time_t                 mtime);
gboolean               gde2_desktop_thumbnail_factory_can_thumbnail (MateDesktopThumbnailFactory *factory,
								      const char            *uri,
								      const char            *mime_type,
								      time_t                 mtime);
GdkPixbuf *            gde2_desktop_thumbnail_factory_generate_thumbnail (MateDesktopThumbnailFactory *factory,
									   const char            *uri,
									   const char            *mime_type);
void                   gde2_desktop_thumbnail_factory_save_thumbnail (MateDesktopThumbnailFactory *factory,
								       GdkPixbuf             *thumbnail,
								       const char            *uri,
								       time_t                 original_mtime);
void                   gde2_desktop_thumbnail_factory_create_failed_thumbnail (MateDesktopThumbnailFactory *factory,
										const char            *uri,
										time_t                 mtime);


/* Thumbnailing utils: */
gboolean   gde2_desktop_thumbnail_has_uri           (GdkPixbuf          *pixbuf,
						      const char         *uri);
gboolean   gde2_desktop_thumbnail_is_valid          (GdkPixbuf          *pixbuf,
						      const char         *uri,
						      time_t              mtime);
char *     gde2_desktop_thumbnail_md5               (const char         *uri);
char *     gde2_desktop_thumbnail_path_for_uri      (const char         *uri,
						      MateDesktopThumbnailSize  size);


/* Pixbuf utils */

GdkPixbuf *gde2_desktop_thumbnail_scale_down_pixbuf (GdkPixbuf          *pixbuf,
						      int                 dest_width,
						      int                 dest_height);

G_END_DECLS

#endif /* GDE2_DESKTOP_THUMBNAIL_H */