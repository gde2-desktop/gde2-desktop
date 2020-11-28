/* gde2-rr.h
 *
 * Copyright 2007, 2008, Red Hat, Inc.
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
 * Author: Soren Sandmann <sandmann@redhat.com>
 */
#ifndef GDE2_RR_H
#define GDE2_RR_H

#ifndef GDE2_DESKTOP_USE_UNSTABLE_API
#error    MateRR is unstable API. You must define GDE2_DESKTOP_USE_UNSTABLE_API before including gde2rr.h
#endif

#include <glib.h>
#include <gdk/gdk.h>

typedef struct MateRRScreenPrivate MateRRScreenPrivate;
typedef struct MateRROutput MateRROutput;
typedef struct MateRRCrtc MateRRCrtc;
typedef struct MateRRMode MateRRMode;

typedef struct {
    GObject parent;

    MateRRScreenPrivate* priv;
} MateRRScreen;

typedef struct {
    GObjectClass parent_class;

        void (* changed) (void);
} MateRRScreenClass;

typedef enum
{
    GDE2_RR_ROTATION_0 =	(1 << 0),
    GDE2_RR_ROTATION_90 =	(1 << 1),
    GDE2_RR_ROTATION_180 =	(1 << 2),
    GDE2_RR_ROTATION_270 =	(1 << 3),
    GDE2_RR_REFLECT_X =	(1 << 4),
    GDE2_RR_REFLECT_Y =	(1 << 5)
} MateRRRotation;

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
} MateRRError;

#define GDE2_RR_CONNECTOR_TYPE_PANEL "Panel"  /* This is a laptop's built-in LCD */

#define GDE2_TYPE_RR_SCREEN                  (gde2_rr_screen_get_type())
#define GDE2_RR_SCREEN(obj)                  (G_TYPE_CHECK_INSTANCE_CAST ((obj), GDE2_TYPE_RR_SCREEN, MateRRScreen))
#define GDE2_IS_RR_SCREEN(obj)               (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDE2_TYPE_RR_SCREEN))
#define GDE2_RR_SCREEN_CLASS(klass)          (G_TYPE_CHECK_CLASS_CAST ((klass), GDE2_TYPE_RR_SCREEN, MateRRScreenClass))
#define GDE2_IS_RR_SCREEN_CLASS(klass)       (G_TYPE_CHECK_CLASS_TYPE ((klass), GDE2_TYPE_RR_SCREEN))
#define GDE2_RR_SCREEN_GET_CLASS(obj)        (G_TYPE_INSTANCE_GET_CLASS ((obj), GDE2_TYPE_RR_SCREEN, MateRRScreenClass))

#define GDE2_TYPE_RR_OUTPUT (gde2_rr_output_get_type())
#define GDE2_TYPE_RR_CRTC   (gde2_rr_crtc_get_type())
#define GDE2_TYPE_RR_MODE   (gde2_rr_mode_get_type())

GType gde2_rr_screen_get_type (void);
GType gde2_rr_output_get_type (void);
GType gde2_rr_crtc_get_type (void);
GType gde2_rr_mode_get_type (void);

/* MateRRScreen */
MateRRScreen * gde2_rr_screen_new                (GdkScreen             *screen,
						    GError               **error);
MateRROutput **gde2_rr_screen_list_outputs       (MateRRScreen         *screen);
MateRRCrtc **  gde2_rr_screen_list_crtcs         (MateRRScreen         *screen);
MateRRMode **  gde2_rr_screen_list_modes         (MateRRScreen         *screen);
MateRRMode **  gde2_rr_screen_list_clone_modes   (MateRRScreen	  *screen);
void            gde2_rr_screen_set_size           (MateRRScreen         *screen,
						    int                    width,
						    int                    height,
						    int                    mm_width,
						    int                    mm_height);
MateRRCrtc *   gde2_rr_screen_get_crtc_by_id     (MateRRScreen         *screen,
						    guint32                id);
gboolean        gde2_rr_screen_refresh            (MateRRScreen         *screen,
						    GError               **error);
MateRROutput * gde2_rr_screen_get_output_by_id   (MateRRScreen         *screen,
						    guint32                id);
MateRROutput * gde2_rr_screen_get_output_by_name (MateRRScreen         *screen,
						    const char            *name);
void            gde2_rr_screen_get_ranges         (MateRRScreen         *screen,
						    int                   *min_width,
						    int                   *max_width,
						    int                   *min_height,
						    int                   *max_height);
void            gde2_rr_screen_get_timestamps     (MateRRScreen         *screen,
						    guint32               *change_timestamp_ret,
						    guint32               *config_timestamp_ret);

void            gde2_rr_screen_set_primary_output (MateRRScreen         *screen,
                                                    MateRROutput         *output);

/* MateRROutput */
guint32         gde2_rr_output_get_id             (MateRROutput         *output);
const char *    gde2_rr_output_get_name           (MateRROutput         *output);
gboolean        gde2_rr_output_is_connected       (MateRROutput         *output);
int             gde2_rr_output_get_size_inches    (MateRROutput         *output);
int             gde2_rr_output_get_width_mm       (MateRROutput         *outout);
int             gde2_rr_output_get_height_mm      (MateRROutput         *output);
const guint8 *  gde2_rr_output_get_edid_data      (MateRROutput         *output);
MateRRCrtc **  gde2_rr_output_get_possible_crtcs (MateRROutput         *output);
MateRRMode *   gde2_rr_output_get_current_mode   (MateRROutput         *output);
MateRRCrtc *   gde2_rr_output_get_crtc           (MateRROutput         *output);
const char *    gde2_rr_output_get_connector_type (MateRROutput         *output);
gboolean        gde2_rr_output_is_laptop          (MateRROutput         *output);
void            gde2_rr_output_get_position       (MateRROutput         *output,
						    int                   *x,
						    int                   *y);
gboolean        gde2_rr_output_can_clone          (MateRROutput         *output,
						    MateRROutput         *clone);
MateRRMode **  gde2_rr_output_list_modes         (MateRROutput         *output);
MateRRMode *   gde2_rr_output_get_preferred_mode (MateRROutput         *output);
gboolean        gde2_rr_output_supports_mode      (MateRROutput         *output,
						    MateRRMode           *mode);
gboolean        gde2_rr_output_get_is_primary     (MateRROutput         *output);

/* MateRRMode */
guint32         gde2_rr_mode_get_id               (MateRRMode           *mode);
guint           gde2_rr_mode_get_width            (MateRRMode           *mode);
guint           gde2_rr_mode_get_height           (MateRRMode           *mode);
int             gde2_rr_mode_get_freq             (MateRRMode           *mode);

/* MateRRCrtc */
guint32         gde2_rr_crtc_get_id               (MateRRCrtc           *crtc);

#ifndef GDE2_DISABLE_DEPRECATED
gboolean        gde2_rr_crtc_set_config           (MateRRCrtc           *crtc,
						    int                    x,
						    int                    y,
						    MateRRMode           *mode,
						    MateRRRotation        rotation,
						    MateRROutput        **outputs,
						    int                    n_outputs,
						    GError               **error);
#endif

gboolean        gde2_rr_crtc_set_config_with_time (MateRRCrtc           *crtc,
						    guint32                timestamp,
						    int                    x,
						    int                    y,
						    MateRRMode           *mode,
						    MateRRRotation        rotation,
						    MateRROutput        **outputs,
						    int                    n_outputs,
						    GError               **error);
gboolean        gde2_rr_crtc_can_drive_output     (MateRRCrtc           *crtc,
						    MateRROutput         *output);
MateRRMode *   gde2_rr_crtc_get_current_mode     (MateRRCrtc           *crtc);
void            gde2_rr_crtc_get_position         (MateRRCrtc           *crtc,
						    int                   *x,
						    int                   *y);
MateRRRotation gde2_rr_crtc_get_current_rotation (MateRRCrtc           *crtc);
MateRRRotation gde2_rr_crtc_get_rotations        (MateRRCrtc           *crtc);
gboolean        gde2_rr_crtc_supports_rotation    (MateRRCrtc           *crtc,
						    MateRRRotation        rotation);

gboolean        gde2_rr_crtc_get_gamma            (MateRRCrtc           *crtc,
						    int                   *size,
						    unsigned short       **red,
						    unsigned short       **green,
						    unsigned short       **blue);
void            gde2_rr_crtc_set_gamma            (MateRRCrtc           *crtc,
						    int                    size,
						    unsigned short        *red,
						    unsigned short        *green,
						    unsigned short        *blue);
#endif /* GDE2_RR_H */
