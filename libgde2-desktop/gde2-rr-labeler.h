/* gde2-rr-labeler.h - Utility to label monitors to identify them
 * while they are being configured.
 *
 * Copyright 2008, Novell, Inc.
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
 * Author: Federico Mena-Quintero <federico@novell.com>
 */

#ifndef GDE2_RR_LABELER_H
#define GDE2_RR_LABELER_H

#ifndef GDE2_DESKTOP_USE_UNSTABLE_API
#error    MateRR is unstable API. You must define GDE2_DESKTOP_USE_UNSTABLE_API before including gde2rr.h
#endif

#include "gde2-rr-config.h"

#define GDE2_TYPE_RR_LABELER            (gde2_rr_labeler_get_type ())
#define GDE2_RR_LABELER(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GDE2_TYPE_RR_LABELER, MateRRLabeler))
#define GDE2_RR_LABELER_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass),  GDE2_TYPE_RR_LABELER, MateRRLabelerClass))
#define GDE2_IS_RR_LABELER(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GDE2_TYPE_RR_LABELER))
#define GDE2_IS_RR_LABELER_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass),  GDE2_TYPE_RR_LABELER))
#define GDE2_RR_LABELER_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj),  GDE2_TYPE_RR_LABELER, MateRRLabelerClass))

typedef struct _MateRRLabeler MateRRLabeler;
typedef struct _MateRRLabelerClass MateRRLabelerClass;
typedef struct _MateRRLabelerPrivate MateRRLabelerPrivate;

struct _MateRRLabeler {
	GObject parent;

	/*< private >*/
	MateRRLabelerPrivate *priv;
};

struct _MateRRLabelerClass {
	GObjectClass parent_class;
};

GType gde2_rr_labeler_get_type (void);

MateRRLabeler *gde2_rr_labeler_new (MateRRConfig *config);

void gde2_rr_labeler_hide (MateRRLabeler *labeler);

#ifdef GDK_VERSION_3_0
void gde2_rr_labeler_get_rgba_for_output (MateRRLabeler *labeler, MateRROutputInfo *output, GdkRGBA *color_out);
#endif
void gde2_rr_labeler_get_color_for_output (MateRRLabeler *labeler, MateRROutputInfo *output, GdkColor *color_out);

#endif
