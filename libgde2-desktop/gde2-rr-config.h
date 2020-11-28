/* gde2-rr-config.h
 * -*- c-basic-offset: 4 -*-
 *
 * Copyright 2007, 2008, Red Hat, Inc.
 * Copyright 2010 Giovanni Campagna
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
 * Author: Soren Sandmann <sandmann@redhat.com>
 */
#ifndef GDE2_RR_CONFIG_H
#define GDE2_RR_CONFIG_H

#ifndef GDE2_DESKTOP_USE_UNSTABLE_API
#error   gde2-rr-config.h is unstable API. You must define GDE2_DESKTOP_USE_UNSTABLE_API before including gde2-rr-config.h
#endif

#include "gde2-rr.h"
#include <glib.h>
#include <glib-object.h>

typedef struct Gde2RROutputInfoPrivate Gde2RROutputInfoPrivate;
typedef struct Gde2RRConfigPrivate Gde2RRConfigPrivate;

typedef struct
{
    GObject parent;

    /*< private >*/
    Gde2RROutputInfoPrivate *priv;
} Gde2RROutputInfo;

typedef struct
{
    GObjectClass parent_class;
} Gde2RROutputInfoClass;

#define GDE2_TYPE_RR_OUTPUT_INFO                  (gde2_rr_output_info_get_type())
#define GDE2_RR_OUTPUT_INFO(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GDE2_TYPE_RR_OUTPUT_INFO, Gde2RROutputInfo))
#define GDE2_IS_RR_OUTPUT_INFO(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDE2_TYPE_RR_OUTPUT_INFO))
#define GDE2_RR_OUTPUT_INFO_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GDE2_TYPE_RR_OUTPUT_INFO, Gde2RROutputInfoClass))
#define GDE2_IS_RR_OUTPUT_INFO_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GDE2_TYPE_RR_OUTPUT_INFO))
#define GDE2_RR_OUTPUT_INFO_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GDE2_TYPE_RR_OUTPUT_INFO, Gde2RROutputInfoClass))

GType gde2_rr_output_info_get_type (void);

char *gde2_rr_output_info_get_name (Gde2RROutputInfo *self);

gboolean gde2_rr_output_info_is_active  (Gde2RROutputInfo *self);
void     gde2_rr_output_info_set_active (Gde2RROutputInfo *self, gboolean active);


void gde2_rr_output_info_get_geometry (Gde2RROutputInfo *self, int *x, int *y, int *width, int *height);
void gde2_rr_output_info_set_geometry (Gde2RROutputInfo *self, int  x, int  y, int  width, int  height);

int  gde2_rr_output_info_get_refresh_rate (Gde2RROutputInfo *self);
void gde2_rr_output_info_set_refresh_rate (Gde2RROutputInfo *self, int rate);

Gde2RRRotation gde2_rr_output_info_get_rotation (Gde2RROutputInfo *self);
void            gde2_rr_output_info_set_rotation (Gde2RROutputInfo *self, Gde2RRRotation rotation);

gboolean gde2_rr_output_info_is_connected     (Gde2RROutputInfo *self);
void     gde2_rr_output_info_get_vendor       (Gde2RROutputInfo *self, gchar* vendor);
guint    gde2_rr_output_info_get_product      (Gde2RROutputInfo *self);
guint    gde2_rr_output_info_get_serial       (Gde2RROutputInfo *self);
double   gde2_rr_output_info_get_aspect_ratio (Gde2RROutputInfo *self);
char    *gde2_rr_output_info_get_display_name (Gde2RROutputInfo *self);

gboolean gde2_rr_output_info_get_primary (Gde2RROutputInfo *self);
void     gde2_rr_output_info_set_primary (Gde2RROutputInfo *self, gboolean primary);

int gde2_rr_output_info_get_preferred_width  (Gde2RROutputInfo *self);
int gde2_rr_output_info_get_preferred_height (Gde2RROutputInfo *self);

typedef struct
{
    GObject parent;

    /*< private >*/
    Gde2RRConfigPrivate *priv;
} Gde2RRConfig;

typedef struct
{
    GObjectClass parent_class;
} Gde2RRConfigClass;

#define GDE2_TYPE_RR_CONFIG                  (gde2_rr_config_get_type())
#define GDE2_RR_CONFIG(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GDE2_TYPE_RR_CONFIG, Gde2RRConfig))
#define GDE2_IS_RR_CONFIG(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDE2_TYPE_RR_CONFIG))
#define GDE2_RR_CONFIG_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GDE2_TYPE_RR_CONFIG, Gde2RRConfigClass))
#define GDE2_IS_RR_CONFIG_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GDE2_TYPE_RR_CONFIG))
#define GDE2_RR_CONFIG_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GDE2_TYPE_RR_CONFIG, Gde2RRConfigClass))

GType               gde2_rr_config_get_type     (void);

Gde2RRConfig      *gde2_rr_config_new_current  (Gde2RRScreen  *screen,
						  GError        **error);
Gde2RRConfig      *gde2_rr_config_new_stored   (Gde2RRScreen  *screen,
						  GError        **error);
gboolean                gde2_rr_config_load_current (Gde2RRConfig  *self,
						      GError        **error);
gboolean                gde2_rr_config_load_filename (Gde2RRConfig  *self,
						       const gchar    *filename,
						       GError        **error);
gboolean            gde2_rr_config_match        (Gde2RRConfig  *config1,
						  Gde2RRConfig  *config2);
gboolean            gde2_rr_config_equal	 (Gde2RRConfig  *config1,
						  Gde2RRConfig  *config2);
gboolean            gde2_rr_config_save         (Gde2RRConfig  *configuration,
						  GError        **error);
void                gde2_rr_config_sanitize     (Gde2RRConfig  *configuration);
gboolean            gde2_rr_config_ensure_primary (Gde2RRConfig  *configuration);

gboolean	    gde2_rr_config_apply_with_time (Gde2RRConfig  *configuration,
						     Gde2RRScreen  *screen,
						     guint32         timestamp,
						     GError        **error);

gboolean            gde2_rr_config_apply_from_filename_with_time (Gde2RRScreen  *screen,
								   const char     *filename,
								   guint32         timestamp,
								   GError        **error);

gboolean            gde2_rr_config_applicable   (Gde2RRConfig  *configuration,
						  Gde2RRScreen  *screen,
						  GError        **error);

gboolean            gde2_rr_config_get_clone    (Gde2RRConfig  *configuration);
void                gde2_rr_config_set_clone    (Gde2RRConfig  *configuration, gboolean clone);
Gde2RROutputInfo **gde2_rr_config_get_outputs  (Gde2RRConfig  *configuration);

char *gde2_rr_config_get_backup_filename (void);
char *gde2_rr_config_get_intended_filename (void);

#endif
