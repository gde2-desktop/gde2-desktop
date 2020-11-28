/* gde2-bg.h -

   Copyright (C) 2007 Red Hat, Inc.
   Copyright (C) 2012 Jasmine Hassan <jasmine.aura@gmail.com>

   This file is part of the Gde2 Library.

   The Gde2 Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   The Gde2 Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with the Gde2 Library; see the file COPYING.LIB.  If not,
   write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
   Boston, MA  02110-1301, USA.

   Authors: Soren Sandmann <sandmann@redhat.com>
	    Jasmine Hassan <jasmine.aura@gmail.com>
*/

#ifndef __GDE2_BG_H__
#define __GDE2_BG_H__

#ifndef GDE2_DESKTOP_USE_UNSTABLE_API
#error    Gde2BG is unstable API. You must define GDE2_DESKTOP_USE_UNSTABLE_API before including gde2-bg.h
#endif

#include <glib.h>
#include <gdk/gdk.h>
#include <gio/gio.h>
#include "gde2-desktop-thumbnail.h"
#include "gde2-bg-crossfade.h"

G_BEGIN_DECLS

#define GDE2_TYPE_BG            (gde2_bg_get_type ())
#define GDE2_BG(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GDE2_TYPE_BG, Gde2BG))
#define GDE2_BG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GDE2_TYPE_BG, Gde2BGClass))
#define GDE2_IS_BG(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDE2_TYPE_BG))
#define GDE2_IS_BG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GDE2_TYPE_BG))
#define GDE2_BG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GDE2_TYPE_BG, Gde2BGClass))

#define GDE2_BG_SCHEMA "org.gde2.background"

/* whether to draw the desktop bg */
#define GDE2_BG_KEY_DRAW_BACKGROUND	"draw-background"

/* whether Caja or gde2-settings-daemon draw the desktop */
#define GDE2_BG_KEY_SHOW_DESKTOP	"show-desktop-icons"

/* whether to fade when changing background (By Caja/m-s-d) */
#define GDE2_BG_KEY_BACKGROUND_FADE	"background-fade"

#define GDE2_BG_KEY_PRIMARY_COLOR	"primary-color"
#define GDE2_BG_KEY_SECONDARY_COLOR	"secondary-color"
#define GDE2_BG_KEY_COLOR_TYPE		"color-shading-type"
#define GDE2_BG_KEY_PICTURE_PLACEMENT	"picture-options"
#define GDE2_BG_KEY_PICTURE_OPACITY	"picture-opacity"
#define GDE2_BG_KEY_PICTURE_FILENAME	"picture-filename"

typedef struct _Gde2BG Gde2BG;
typedef struct _Gde2BGClass Gde2BGClass;

typedef enum {
	GDE2_BG_COLOR_SOLID,
	GDE2_BG_COLOR_H_GRADIENT,
	GDE2_BG_COLOR_V_GRADIENT
} Gde2BGColorType;

typedef enum {
	GDE2_BG_PLACEMENT_TILED,
	GDE2_BG_PLACEMENT_ZOOMED,
	GDE2_BG_PLACEMENT_CENTERED,
	GDE2_BG_PLACEMENT_SCALED,
	GDE2_BG_PLACEMENT_FILL_SCREEN,
	GDE2_BG_PLACEMENT_SPANNED
} Gde2BGPlacement;

GType            gde2_bg_get_type              (void);
Gde2BG *         gde2_bg_new                   (void);
void             gde2_bg_load_from_preferences (Gde2BG               *bg);
void             gde2_bg_load_from_system_preferences  (Gde2BG       *bg);
void             gde2_bg_load_from_system_gsettings    (Gde2BG       *bg,
							GSettings    *settings,
							gboolean      reset_apply);
void             gde2_bg_load_from_gsettings   (Gde2BG               *bg,
						GSettings            *settings);
void             gde2_bg_save_to_preferences   (Gde2BG               *bg);
void             gde2_bg_save_to_gsettings     (Gde2BG               *bg,
						GSettings            *settings);

/* Setters */
void             gde2_bg_set_filename          (Gde2BG               *bg,
						 const char            *filename);
void             gde2_bg_set_placement         (Gde2BG               *bg,
						 Gde2BGPlacement       placement);
void             gde2_bg_set_color             (Gde2BG               *bg,
						 Gde2BGColorType       type,
#if GTK_CHECK_VERSION(3, 0, 0)
						 GdkRGBA              *primary,
						 GdkRGBA              *secondary);
#else
						 GdkColor              *primary,
						 GdkColor              *secondary);
#endif
void		 gde2_bg_set_draw_background   (Gde2BG		     *bg,
						gboolean	      draw_background);
/* Getters */
gboolean	 gde2_bg_get_draw_background   (Gde2BG		     *bg);
Gde2BGPlacement  gde2_bg_get_placement         (Gde2BG               *bg);
void		 gde2_bg_get_color             (Gde2BG               *bg,
						 Gde2BGColorType      *type,
#if GTK_CHECK_VERSION(3, 0, 0)
						 GdkRGBA              *primary,
						 GdkRGBA              *secondary);
#else
						 GdkColor              *primary,
						 GdkColor              *secondary);
#endif
const gchar *    gde2_bg_get_filename          (Gde2BG               *bg);

/* Drawing and thumbnailing */
void             gde2_bg_draw                  (Gde2BG               *bg,
						 GdkPixbuf             *dest,
						 GdkScreen	       *screen,
                                                 gboolean               is_root);

#if GTK_CHECK_VERSION(3, 0, 0)
cairo_surface_t *gde2_bg_create_surface        (Gde2BG               *bg,
#else
GdkPixmap       *gde2_bg_create_pixmap         (Gde2BG               *bg,
#endif
						GdkWindow            *window,
						int                   width,
						int                   height,
						gboolean              root);

gboolean         gde2_bg_get_image_size        (Gde2BG               *bg,
						 Gde2DesktopThumbnailFactory *factory,
                                                 int                    best_width,
                                                 int                    best_height,
						 int                   *width,
						 int                   *height);
GdkPixbuf *      gde2_bg_create_thumbnail      (Gde2BG               *bg,
						 Gde2DesktopThumbnailFactory *factory,
						 GdkScreen             *screen,
						 int                    dest_width,
						 int                    dest_height);
gboolean         gde2_bg_is_dark               (Gde2BG               *bg,
                                                 int                    dest_width,
						 int                    dest_height);
gboolean         gde2_bg_has_multiple_sizes    (Gde2BG               *bg);
gboolean         gde2_bg_changes_with_time     (Gde2BG               *bg);
GdkPixbuf *      gde2_bg_create_frame_thumbnail (Gde2BG              *bg,
						 Gde2DesktopThumbnailFactory *factory,
						 GdkScreen             *screen,
						 int                    dest_width,
						 int                    dest_height,
						 int                    frame_num);

/* Set a surface as root - not a Gde2BG method. At some point
 * if we decide to stabilize the API then we may want to make
 * these object methods, drop gde2_bg_create_surface, etc.
 */
#if GTK_CHECK_VERSION(3, 0, 0)
void             gde2_bg_set_surface_as_root   (GdkScreen            *screen,
						cairo_surface_t    *surface);
Gde2BGCrossfade *gde2_bg_set_surface_as_root_with_crossfade (GdkScreen       *screen,
							     cairo_surface_t *surface);
cairo_surface_t *gde2_bg_get_surface_from_root (GdkScreen *screen);

#else /* GTK_CHECK_VERSION(3, 0, 0) */

void             gde2_bg_set_pixmap_as_root    (GdkScreen          *screen,
						GdkPixmap          *pixmap);
Gde2BGCrossfade *gde2_bg_set_pixmap_as_root_with_crossfade  (GdkScreen       *screen,
							     GdkPixmap       *pixmap);
GdkPixmap *gde2_bg_get_pixmap_from_root (GdkScreen *screen);
#endif /* GTK_CHECK_VERSION(3, 0, 0) */

G_END_DECLS

#endif
