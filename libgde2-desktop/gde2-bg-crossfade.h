/* gde2-bg-crossfade.h - fade window background between two pixmaps

   Copyright 2008, Red Hat, Inc.

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
   write to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
   Floor, Boston, MA 02110-1301 US.

   Author: Ray Strode <rstrode@redhat.com>
*/

#ifndef __GDE2_BG_CROSSFADE_H__
#define __GDE2_BG_CROSSFADE_H__

#ifndef GDE2_DESKTOP_USE_UNSTABLE_API
#error    Gde2BGCrossfade is unstable API. You must define GDE2_DESKTOP_USE_UNSTABLE_API before including gde2-bg-crossfade.h
#endif

#include <glib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GDE2_TYPE_BG_CROSSFADE            (gde2_bg_crossfade_get_type ())
#define GDE2_BG_CROSSFADE(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GDE2_TYPE_BG_CROSSFADE, Gde2BGCrossfade))
#define GDE2_BG_CROSSFADE_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GDE2_TYPE_BG_CROSSFADE, Gde2BGCrossfadeClass))
#define GDE2_IS_BG_CROSSFADE(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDE2_TYPE_BG_CROSSFADE))
#define GDE2_IS_BG_CROSSFADE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GDE2_TYPE_BG_CROSSFADE))
#define GDE2_BG_CROSSFADE_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GDE2_TYPE_BG_CROSSFADE, Gde2BGCrossfadeClass))

typedef struct _Gde2BGCrossfadePrivate Gde2BGCrossfadePrivate;
typedef struct _Gde2BGCrossfade Gde2BGCrossfade;
typedef struct _Gde2BGCrossfadeClass Gde2BGCrossfadeClass;

struct _Gde2BGCrossfade
{
	GObject parent_object;

	Gde2BGCrossfadePrivate *priv;
};

struct _Gde2BGCrossfadeClass
{
	GObjectClass parent_class;

	void (* finished) (Gde2BGCrossfade *fade, GdkWindow *window);
};

GType             gde2_bg_crossfade_get_type              (void);
Gde2BGCrossfade *gde2_bg_crossfade_new (int width, int height);


#if GTK_CHECK_VERSION(3, 0, 0)
gboolean          gde2_bg_crossfade_set_start_surface (Gde2BGCrossfade *fade,
						       cairo_surface_t *surface);
gboolean          gde2_bg_crossfade_set_end_surface (Gde2BGCrossfade *fade,
						     cairo_surface_t *surface);
#else
gboolean          gde2_bg_crossfade_set_start_pixmap (Gde2BGCrossfade *fade,
						      GdkPixmap *pixmap);
gboolean          gde2_bg_crossfade_set_end_pixmap (Gde2BGCrossfade *fade,
						    GdkPixmap *pixmap);
#endif

void              gde2_bg_crossfade_start (Gde2BGCrossfade *fade,
                                           GdkWindow       *window);
void              gde2_bg_crossfade_start_widget (Gde2BGCrossfade *fade,
                                                  GtkWidget       *widget);
gboolean          gde2_bg_crossfade_is_started (Gde2BGCrossfade *fade);
void              gde2_bg_crossfade_stop (Gde2BGCrossfade *fade);

G_END_DECLS

#endif
