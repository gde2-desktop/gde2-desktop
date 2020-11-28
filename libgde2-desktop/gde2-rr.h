/* gde2-rr.h
 *
 * Copyright 2007, 2008, Red Hat, Inc.
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
#ifndef GDE2_RR_H
#define GDE2_RR_H

#ifndef GDE2_DESKTOP_USE_UNSTABLE_API
#error    Gde2RR is unstable API. You must define GDE2_DESKTOP_USE_UNSTABLE_API before including gde2rr.h
#endif

#include <glib.h>
#include <gdk/gdk.h>

typedef struct Gde2RRScreenPrivate Gde2RRScreenPrivate;
typedef struct Gde2RROutput Gde2RROutput;
typedef struct Gde2RRCrtc Gde2RRCrtc;
typedef struct Gde2RRMode Gde2RRMode;

typedef struct {
    GObject parent;

    Gde2RRScreenPrivate* priv;
} Gde2RRScreen;

typedef struct {
    GObjectClass parent_class;

        void (* changed) (void);
} Gde2RRScreenClass;

typedef enum
{
    GDE2_RR_ROTATION_0 =	(1 << 0),
    GDE2_RR_ROTATION_90 =	(1 << 1),
    GDE2_RR_ROTATION_180 =	(1 << 2),
    GDE2_RR_ROTATION_270 =	(1 << 3),
    GDE2_RR_REFLECT_X =	(1 << 4),
    GDE2_RR_REFLECT_Y =	(1 << 5)
} Gde2RRRotation;

/* Error codes */

#define GDE2_RR_ERROR (gde2_rr_error_quark ())

GQuark gde2_rr_error_quark (void);

typedef enum {
    GDE2_RR_ERROR_UNKNOWN,		/* generic "fail" */
    GDE2_RR_ERROR_NO_RANDR_EXTENSION,	/* RANDR extension is not present */
    GDE2_RR_ERROR_RANDR_ERROR,		/* generic/undescribed error from the underlying XRR API */
    GDE2_RR_ERROR_BOUNDS_ERROR,	/* requested bounds of a CRTC are outside the maximum size */
    GDE2_RR_ERROR_CRTC_ASSIGNMENT,	/* could not assign CRTCs to outputs */
    GDE2_RR_ERROR_NO_MATCHING_CONFIG,	/* none of the saved configurations matched the current configuration */
} Gde2RRError;

#define GDE2_RR_CONNECTOR_TYPE_PANEL "Panel"  /* This is a laptop's built-in LCD */

#define GDE2_TYPE_RR_SCREEN                  (gde2_rr_screen_get_type())
#define GDE2_RR_SCREEN(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GDE2_TYPE_RR_SCREEN, Gde2RRScreen))
#define GDE2_IS_RR_SCREEN(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDE2_TYPE_RR_SCREEN))
#define GDE2_RR_SCREEN_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GDE2_TYPE_RR_SCREEN, Gde2RRScreenClass))
#define GDE2_IS_RR_SCREEN_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GDE2_TYPE_RR_SCREEN))
#define GDE2_RR_SCREEN_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GDE2_TYPE_RR_SCREEN, Gde2RRScreenClass))

#define GDE2_TYPE_RR_OUTPUT (gde2_rr_output_get_type())
#define GDE2_TYPE_RR_CRTC   (gde2_rr_crtc_get_type())
#define GDE2_TYPE_RR_MODE   (gde2_rr_mode_get_type())

GType gde2_rr_screen_get_type (void);
GType gde2_rr_output_get_type (void);
GType gde2_rr_crtc_get_type (void);
GType gde2_rr_mode_get_type (void);

/* Gde2RRScreen */
Gde2RRScreen * gde2_rr_screen_new                (GdkScreen             *screen,
						    GError               **error);
Gde2RROutput **gde2_rr_screen_list_outputs       (Gde2RRScreen         *screen);
Gde2RRCrtc **  gde2_rr_screen_list_crtcs         (Gde2RRScreen         *screen);
Gde2RRMode **  gde2_rr_screen_list_modes         (Gde2RRScreen         *screen);
Gde2RRMode **  gde2_rr_screen_list_clone_modes   (Gde2RRScreen	  *screen);
void            gde2_rr_screen_set_size           (Gde2RRScreen         *screen,
						    int                    width,
						    int                    height,
						    int                    mm_width,
						    int                    mm_height);
Gde2RRCrtc *   gde2_rr_screen_get_crtc_by_id     (Gde2RRScreen         *screen,
						    guint32                id);
gboolean        gde2_rr_screen_refresh            (Gde2RRScreen         *screen,
						    GError               **error);
Gde2RROutput * gde2_rr_screen_get_output_by_id   (Gde2RRScreen         *screen,
						    guint32                id);
Gde2RROutput * gde2_rr_screen_get_output_by_name (Gde2RRScreen         *screen,
						    const char            *name);
void            gde2_rr_screen_get_ranges         (Gde2RRScreen         *screen,
						    int                   *min_width,
						    int                   *max_width,
						    int                   *min_height,
						    int                   *max_height);
void            gde2_rr_screen_get_timestamps     (Gde2RRScreen         *screen,
						    guint32               *change_timestamp_ret,
						    guint32               *config_timestamp_ret);

void            gde2_rr_screen_set_primary_output (Gde2RRScreen         *screen,
                                                    Gde2RROutput         *output);

/* Gde2RROutput */
guint32         gde2_rr_output_get_id             (Gde2RROutput         *output);
const char *    gde2_rr_output_get_name           (Gde2RROutput         *output);
gboolean        gde2_rr_output_is_connected       (Gde2RROutput         *output);
int             gde2_rr_output_get_size_inches    (Gde2RROutput         *output);
int             gde2_rr_output_get_width_mm       (Gde2RROutput         *outout);
int             gde2_rr_output_get_height_mm      (Gde2RROutput         *output);
const guint8 *  gde2_rr_output_get_edid_data      (Gde2RROutput         *output);
Gde2RRCrtc **  gde2_rr_output_get_possible_crtcs (Gde2RROutput         *output);
Gde2RRMode *   gde2_rr_output_get_current_mode   (Gde2RROutput         *output);
Gde2RRCrtc *   gde2_rr_output_get_crtc           (Gde2RROutput         *output);
const char *    gde2_rr_output_get_connector_type (Gde2RROutput         *output);
gboolean        gde2_rr_output_is_laptop          (Gde2RROutput         *output);
void            gde2_rr_output_get_position       (Gde2RROutput         *output,
						    int                   *x,
						    int                   *y);
gboolean        gde2_rr_output_can_clone          (Gde2RROutput         *output,
						    Gde2RROutput         *clone);
Gde2RRMode **  gde2_rr_output_list_modes         (Gde2RROutput         *output);
Gde2RRMode *   gde2_rr_output_get_preferred_mode (Gde2RROutput         *output);
gboolean        gde2_rr_output_supports_mode      (Gde2RROutput         *output,
						    Gde2RRMode           *mode);
gboolean        gde2_rr_output_get_is_primary     (Gde2RROutput         *output);

/* Gde2RRMode */
guint32         gde2_rr_mode_get_id               (Gde2RRMode           *mode);
guint           gde2_rr_mode_get_width            (Gde2RRMode           *mode);
guint           gde2_rr_mode_get_height           (Gde2RRMode           *mode);
int             gde2_rr_mode_get_freq             (Gde2RRMode           *mode);

/* Gde2RRCrtc */
guint32         gde2_rr_crtc_get_id               (Gde2RRCrtc           *crtc);

#ifndef GDE2_DISABLE_DEPRECATED
gboolean        gde2_rr_crtc_set_config           (Gde2RRCrtc           *crtc,
						    int                    x,
						    int                    y,
						    Gde2RRMode           *mode,
						    Gde2RRRotation        rotation,
						    Gde2RROutput        **outputs,
						    int                    n_outputs,
						    GError               **error);
#endif

gboolean        gde2_rr_crtc_set_config_with_time (Gde2RRCrtc           *crtc,
						    guint32                timestamp,
						    int                    x,
						    int                    y,
						    Gde2RRMode           *mode,
						    Gde2RRRotation        rotation,
						    Gde2RROutput        **outputs,
						    int                    n_outputs,
						    GError               **error);
gboolean        gde2_rr_crtc_can_drive_output     (Gde2RRCrtc           *crtc,
						    Gde2RROutput         *output);
Gde2RRMode *   gde2_rr_crtc_get_current_mode     (Gde2RRCrtc           *crtc);
void            gde2_rr_crtc_get_position         (Gde2RRCrtc           *crtc,
						    int                   *x,
						    int                   *y);
Gde2RRRotation gde2_rr_crtc_get_current_rotation (Gde2RRCrtc           *crtc);
Gde2RRRotation gde2_rr_crtc_get_rotations        (Gde2RRCrtc           *crtc);
gboolean        gde2_rr_crtc_supports_rotation    (Gde2RRCrtc           *crtc,
						    Gde2RRRotation        rotation);

gboolean        gde2_rr_crtc_get_gamma            (Gde2RRCrtc           *crtc,
						    int                   *size,
						    unsigned short       **red,
						    unsigned short       **green,
						    unsigned short       **blue);
void            gde2_rr_crtc_set_gamma            (Gde2RRCrtc           *crtc,
						    int                    size,
						    unsigned short        *red,
						    unsigned short        *green,
						    unsigned short        *blue);
#endif /* GDE2_RR_H */
