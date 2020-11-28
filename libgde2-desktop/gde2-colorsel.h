/* GTK - The GIMP Toolkit
 * Copyright (C) 2000 Red Hat, Inc.
 * Copyright (C) 1995-1997 Peter Mattis, Spencer Kimball and Josh MacDonald
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

/*
 * Modified by the GTK+ Team and others 1997-2000.  See the AUTHORS
 * file for a list of people on the GTK+ Team.  See the ChangeLog
 * files for a list of changes.  These files are distributed with
 * GTK+ at ftp://ftp.gtk.org/pub/gtk/.
 */

#ifndef __GDE2_COLOR_SELECTION_H__
#define __GDE2_COLOR_SELECTION_H__

#include <glib.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GDE2_TYPE_COLOR_SELECTION			(gde2_color_selection_get_type ())
#define GDE2_COLOR_SELECTION(obj)			(G_TYPE_CHECK_INSTANCE_CAST ((obj), GDE2_TYPE_COLOR_SELECTION, Gde2ColorSelection))
#define GDE2_COLOR_SELECTION_CLASS(klass)		(G_TYPE_CHECK_CLASS_CAST ((klass), GDE2_TYPE_COLOR_SELECTION, Gde2ColorSelectionClass))
#define GDE2_IS_COLOR_SELECTION(obj)			(G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDE2_TYPE_COLOR_SELECTION))
#define GDE2_IS_COLOR_SELECTION_CLASS(klass)		(G_TYPE_CHECK_CLASS_TYPE ((klass), GDE2_TYPE_COLOR_SELECTION))
#define GDE2_COLOR_SELECTION_GET_CLASS(obj)              (G_TYPE_INSTANCE_GET_CLASS ((obj), GDE2_TYPE_COLOR_SELECTION, Gde2ColorSelectionClass))


typedef struct _Gde2ColorSelection       Gde2ColorSelection;
typedef struct _Gde2ColorSelectionClass  Gde2ColorSelectionClass;
typedef struct _ColorSelectionPrivate    ColorSelectionPrivate;


typedef void (* Gde2ColorSelectionChangePaletteFunc) (const GdkColor    *colors,
                                                     gint               n_colors);
typedef void (* Gde2ColorSelectionChangePaletteWithScreenFunc) (GdkScreen         *screen,
							       const GdkColor    *colors,
							       gint               n_colors);

struct _Gde2ColorSelection
{
  GtkBox parent_instance;

  /* < private_data > */
  ColorSelectionPrivate *private_data;
};

struct _Gde2ColorSelectionClass
{
  GtkBoxClass parent_class;

  void (*color_changed)	(Gde2ColorSelection *color_selection);

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
  void (*_gtk_reserved4) (void);
};


/* ColorSelection */

GType      gde2_color_selection_get_type                (void) G_GNUC_CONST;
GtkWidget *gde2_color_selection_new                     (void);
gboolean   gde2_color_selection_get_has_opacity_control (Gde2ColorSelection *colorsel);
void       gde2_color_selection_set_has_opacity_control (Gde2ColorSelection *colorsel,
							gboolean           has_opacity);
gboolean   gde2_color_selection_get_has_palette         (Gde2ColorSelection *colorsel);
void       gde2_color_selection_set_has_palette         (Gde2ColorSelection *colorsel,
							gboolean           has_palette);


void     gde2_color_selection_set_current_color   (Gde2ColorSelection *colorsel,
						  const GdkColor    *color);
void     gde2_color_selection_set_current_alpha   (Gde2ColorSelection *colorsel,
						  guint16            alpha);
void     gde2_color_selection_get_current_color   (Gde2ColorSelection *colorsel,
						  GdkColor          *color);
guint16  gde2_color_selection_get_current_alpha   (Gde2ColorSelection *colorsel);
void     gde2_color_selection_set_previous_color  (Gde2ColorSelection *colorsel,
						  const GdkColor    *color);
void     gde2_color_selection_set_previous_alpha  (Gde2ColorSelection *colorsel,
						  guint16            alpha);
void     gde2_color_selection_get_previous_color  (Gde2ColorSelection *colorsel,
						  GdkColor          *color);
guint16  gde2_color_selection_get_previous_alpha  (Gde2ColorSelection *colorsel);

gboolean gde2_color_selection_is_adjusting        (Gde2ColorSelection *colorsel);

gboolean gde2_color_selection_palette_from_string (const gchar       *str,
                                                  GdkColor         **colors,
                                                  gint              *n_colors);
gchar*   gde2_color_selection_palette_to_string   (const GdkColor    *colors,
                                                  gint               n_colors);

#ifndef GTK_DISABLE_DEPRECATED
#ifndef GDK_MULTIHEAD_SAFE
Gde2ColorSelectionChangePaletteFunc           gde2_color_selection_set_change_palette_hook             (Gde2ColorSelectionChangePaletteFunc           func);
#endif
#endif

Gde2ColorSelectionChangePaletteWithScreenFunc gde2_color_selection_set_change_palette_with_screen_hook (Gde2ColorSelectionChangePaletteWithScreenFunc func);

#ifndef GTK_DISABLE_DEPRECATED
/* Deprecated calls: */
void gde2_color_selection_set_color         (Gde2ColorSelection *colorsel,
					    gdouble           *color);
void gde2_color_selection_get_color         (Gde2ColorSelection *colorsel,
					    gdouble           *color);
#endif /* GTK_DISABLE_DEPRECATED */

G_END_DECLS

#endif /* __GDE2_COLOR_SELECTION_H__ */
