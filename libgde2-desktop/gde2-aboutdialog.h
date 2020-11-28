/*
 * gde2-aboutdialog.h: Traditional GTK+ About Dialog
 *
 * Copyright (C) 2001 CodeFactory AB
 * Copyright (C) 2001 Anders Carlsson <andersca@codefactory.se>
 * Copyright (C) 2003, 2004 Matthias Clasen <mclasen@redhat.com>
 * Copyright (C) 2014 Stefano Karapetsas <stefano@karapetsas.com>
 *
 * This file is part of the Gde2 Library.
 *
 * The Gde2 Library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * The Gde2 Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with the Gde2 Library; see the file COPYING.LIB.  If not,
 * write to the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301, USA.
 *
 * Author: Stefano Karapetsas <stefano@karapetsas.com>
*/

#ifndef __GDE2_ABOUT_DIALOG_H__
#define __GDE2_ABOUT_DIALOG_H__

#include <glib.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define GDE2_TYPE_ABOUT_DIALOG            (gde2_about_dialog_get_type ())
#define GDE2_ABOUT_DIALOG(object)         (G_TYPE_CHECK_INSTANCE_CAST ((object), GDE2_TYPE_ABOUT_DIALOG, Gde2AboutDialog))
#define GDE2_ABOUT_DIALOG_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GDE2_TYPE_ABOUT_DIALOG, Gde2AboutDialogClass))
#define GDE2_IS_ABOUT_DIALOG(object)      (G_TYPE_CHECK_INSTANCE_TYPE ((object), GDE2_TYPE_ABOUT_DIALOG))
#define GDE2_IS_ABOUT_DIALOG_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GDE2_TYPE_ABOUT_DIALOG))
#define GDE2_ABOUT_DIALOG_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GDE2_TYPE_ABOUT_DIALOG, Gde2AboutDialogClass))

typedef struct _Gde2AboutDialog        Gde2AboutDialog;
typedef struct _Gde2AboutDialogClass   Gde2AboutDialogClass;
typedef struct _Gde2AboutDialogPrivate Gde2AboutDialogPrivate;

/**
 * Gde2AboutDialog:
 *
 * The <structname>Gde2AboutDialog</structname> struct contains
 * only private fields and should not be directly accessed.
 */
struct _Gde2AboutDialog 
{
  GtkDialog parent_instance;

  /*< private >*/
  Gde2AboutDialogPrivate *private_data;
};

struct _Gde2AboutDialogClass
{
  GtkDialogClass parent_class;

  /* Padding for future expansion */
  void (*_gtk_reserved1) (void);
  void (*_gtk_reserved2) (void);
  void (*_gtk_reserved3) (void);
};

GType                  gde2_about_dialog_get_type               (void) G_GNUC_CONST;
GtkWidget             *gde2_about_dialog_new                    (void);
void                   gde2_show_about_dialog                   (GtkWindow       *parent,
                                                                 const gchar     *first_property_name,
                                                                 ...) G_GNUC_NULL_TERMINATED;

const gchar *          gde2_about_dialog_get_program_name       (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_program_name       (Gde2AboutDialog  *about,
                                                                 const gchar      *name);
const gchar *          gde2_about_dialog_get_version            (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_version            (Gde2AboutDialog  *about,
                                                                 const gchar      *version);
const gchar *          gde2_about_dialog_get_copyright          (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_copyright          (Gde2AboutDialog  *about,
                                                                 const gchar      *copyright);
const gchar *          gde2_about_dialog_get_comments           (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_comments           (Gde2AboutDialog  *about,
                                                                 const gchar      *comments);
const gchar *          gde2_about_dialog_get_license            (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_license            (Gde2AboutDialog  *about,
                                                                 const gchar      *license);

gboolean               gde2_about_dialog_get_wrap_license       (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_wrap_license       (Gde2AboutDialog  *about,
                                                                 gboolean          wrap_license);

const gchar *          gde2_about_dialog_get_website            (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_website            (Gde2AboutDialog  *about,
                                                                 const gchar      *website);
const gchar *          gde2_about_dialog_get_website_label      (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_website_label      (Gde2AboutDialog  *about,
                                                                 const gchar      *website_label);
const gchar* const *   gde2_about_dialog_get_authors            (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_authors            (Gde2AboutDialog  *about,
                                                                 const gchar     **authors);
const gchar* const *   gde2_about_dialog_get_documenters        (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_documenters        (Gde2AboutDialog  *about,
                                                                 const gchar     **documenters);
const gchar* const *   gde2_about_dialog_get_artists            (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_artists            (Gde2AboutDialog  *about,
                                                                 const gchar     **artists);
const gchar *          gde2_about_dialog_get_translator_credits (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_translator_credits (Gde2AboutDialog  *about,
                                                                 const gchar      *translator_credits);
GdkPixbuf             *gde2_about_dialog_get_logo               (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_logo               (Gde2AboutDialog  *about,
                                                                 GdkPixbuf        *logo);
const gchar *          gde2_about_dialog_get_logo_icon_name     (Gde2AboutDialog  *about);
void                   gde2_about_dialog_set_logo_icon_name     (Gde2AboutDialog  *about,
                                                                 const gchar      *icon_name);

G_END_DECLS

#endif /* __GDE2_ABOUT_DIALOG_H__ */


