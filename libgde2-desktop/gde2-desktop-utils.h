/* -*- Mode: C; c-set-style: linux indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/* gde2-ditem.h - Utilities for the GDE2 Desktop

   Copyright (C) 1998 Tom Tromey
   All rights reserved.

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
   Boston, MA  02110-1301, USA.  */
/*
  @NOTATION@
 */

#ifndef GDE2_DESKTOP_UTILS_H
#define GDE2_DESKTOP_UTILS_H

#ifndef GDE2_DESKTOP_USE_UNSTABLE_API
#error    gde2-desktop-utils is unstable API. You must define GDE2_DESKTOP_USE_UNSTABLE_API before including gde2-desktop-utils.h
#endif

#include <glib.h>
#include <gdk/gdk.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

/* prepend the terminal command to a vector */
void gde2_desktop_prepend_terminal_to_vector (int *argc, char ***argv);

/* replace gdk_spawn_command_line_on_screen, not available in GTK3 */
gboolean gde2_gdk_spawn_command_line_on_screen (GdkScreen *screen, const gchar *command, GError **error);

#if GTK_CHECK_VERSION (3, 0, 0)
void
gde2_desktop_gtk_style_get_light_color (GtkStyleContext *style,
                                        GtkStateFlags    state,
                                        GdkRGBA         *color);

void
gde2_desktop_gtk_style_get_dark_color (GtkStyleContext *style,
                                       GtkStateFlags    state,
                                       GdkRGBA         *color);
#endif

G_END_DECLS

#endif /* GDE2_DESKTOP_UTILS_H */
