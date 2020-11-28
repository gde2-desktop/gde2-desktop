/* gde2-rr-output-info.c
 * -*- c-basic-offset: 4 -*-
 *
 * Copyright 2010 Giovanni Campagna
 *
 * This file is part of the Gde2 Desktop Library.
 *
 * The Gde2 Desktop Library is free software; you can redistribute it and/or
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
 * License along with the Gde2 Desktop Library; see the file COPYING.LIB.  If not,
 * write to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#define GDE2_DESKTOP_USE_UNSTABLE_API

#include <config.h>

#include "gde2-rr-config.h"

#include "edid.h"
#include "gde2-rr-private.h"

G_DEFINE_TYPE (Gde2RROutputInfo, gde2_rr_output_info, G_TYPE_OBJECT)

static void
gde2_rr_output_info_init (Gde2RROutputInfo *self)
{
    self->priv = G_TYPE_INSTANCE_GET_PRIVATE (self, GDE2_TYPE_RR_OUTPUT_INFO, Gde2RROutputInfoPrivate);

    self->priv->name = NULL;
    self->priv->on = FALSE;
    self->priv->display_name = NULL;
}

static void
gde2_rr_output_info_finalize (GObject *gobject)
{
    Gde2RROutputInfo *self = GDE2_RR_OUTPUT_INFO (gobject);

    g_free (self->priv->name);
    g_free (self->priv->display_name);

    G_OBJECT_CLASS (gde2_rr_output_info_parent_class)->finalize (gobject);
}

static void
gde2_rr_output_info_class_init (Gde2RROutputInfoClass *klass)
{
    GObjectClass *gobject_class = G_OBJECT_CLASS (klass);

    g_type_class_add_private (klass, sizeof (Gde2RROutputInfoPrivate));

    gobject_class->finalize = gde2_rr_output_info_finalize;
}

/**
 * gde2_rr_output_info_get_name:
 *
 * Returns: (transfer none): the output name
 */
char *gde2_rr_output_info_get_name (Gde2RROutputInfo *self)
{
    g_return_val_if_fail (GDE2_IS_RR_OUTPUT_INFO (self), NULL);

    return self->priv->name;
}

/**
 * gde2_rr_output_info_is_active:
 *
 * Returns: whether there is a CRTC assigned to this output (i.e. a signal is being sent to it)
 */
gboolean gde2_rr_output_info_is_active (Gde2RROutputInfo *self)
{
    g_return_val_if_fail (GDE2_IS_RR_OUTPUT_INFO (self), FALSE);

    return self->priv->on;
}

void gde2_rr_output_info_set_active (Gde2RROutputInfo *self, gboolean active)
{
    g_return_if_fail (GDE2_IS_RR_OUTPUT_INFO (self));

    self->priv->on = active;
}

/**
 * gde2_rr_output_info_get_geometry:
 * @self: a #Gde2RROutputInfo
 * @x: (out) (allow-none):
 * @y: (out) (allow-none):
 * @width: (out) (allow-none):
 * @height: (out) (allow-none):
 */
void gde2_rr_output_info_get_geometry (Gde2RROutputInfo *self, int *x, int *y, int *width, int *height)
{
    g_return_if_fail (GDE2_IS_RR_OUTPUT_INFO (self));

    if (x)
	*x = self->priv->x;
    if (y)
	*y = self->priv->y;
    if (width)
	*width = self->priv->width;
    if (height)
	*height = self->priv->height;
}

/**
 * gde2_rr_output_info_set_geometry:
 * @self: a #Gde2RROutputInfo
 * @x: x offset for monitor
 * @y: y offset for monitor
 * @width: monitor width
 * @height: monitor height
 *
 * Set the geometry for the monitor connected to the specified output.
 */
void gde2_rr_output_info_set_geometry (Gde2RROutputInfo *self, int  x, int  y, int  width, int  height)
{
    g_return_if_fail (GDE2_IS_RR_OUTPUT_INFO (self));

    self->priv->x = x;
    self->priv->y = y;
    self->priv->width = width;
    self->priv->height = height;
}

int gde2_rr_output_info_get_refresh_rate (Gde2RROutputInfo *self)
{
    g_return_val_if_fail (GDE2_IS_RR_OUTPUT_INFO (self), 0);

    return self->priv->rate;
}

void gde2_rr_output_info_set_refresh_rate (Gde2RROutputInfo *self, int rate)
{
    g_return_if_fail (GDE2_IS_RR_OUTPUT_INFO (self));

    self->priv->rate = rate;
}

Gde2RRRotation gde2_rr_output_info_get_rotation (Gde2RROutputInfo *self)
{
    g_return_val_if_fail (GDE2_IS_RR_OUTPUT_INFO (self), GDE2_RR_ROTATION_0);

    return self->priv->rotation;
}

void gde2_rr_output_info_set_rotation (Gde2RROutputInfo *self, Gde2RRRotation rotation)
{
    g_return_if_fail (GDE2_IS_RR_OUTPUT_INFO (self));

    self->priv->rotation = rotation;
}

/**
 * gde2_rr_output_info_is_connected:
 *
 * Returns: whether the output is physically connected to a monitor
 */
gboolean gde2_rr_output_info_is_connected (Gde2RROutputInfo *self)
{
    g_return_val_if_fail (GDE2_IS_RR_OUTPUT_INFO (self), FALSE);

    return self->priv->connected;
}

/**
 * gde2_rr_output_info_get_vendor:
 * @self: a #Gde2RROutputInfo
 * @vendor: (out caller-allocates) (array fixed-size=4):
 */
void gde2_rr_output_info_get_vendor (Gde2RROutputInfo *self, gchar* vendor)
{
    g_return_if_fail (GDE2_IS_RR_OUTPUT_INFO (self));
    g_return_if_fail (vendor != NULL);

    vendor[0] = self->priv->vendor[0];
    vendor[1] = self->priv->vendor[1];
    vendor[2] = self->priv->vendor[2];
    vendor[3] = self->priv->vendor[3];
}

guint gde2_rr_output_info_get_product (Gde2RROutputInfo *self)
{
    g_return_val_if_fail (GDE2_IS_RR_OUTPUT_INFO (self), 0);

    return self->priv->product;
}

guint gde2_rr_output_info_get_serial (Gde2RROutputInfo *self)
{
    g_return_val_if_fail (GDE2_IS_RR_OUTPUT_INFO (self), 0);

    return self->priv->serial;
}

double gde2_rr_output_info_get_aspect_ratio (Gde2RROutputInfo *self)
{
    g_return_val_if_fail (GDE2_IS_RR_OUTPUT_INFO (self), 0);

    return self->priv->aspect;
}

/**
 * gde2_rr_output_info_get_display_name:
 *
 * Returns: (transfer none): the display name of this output
 */
char *gde2_rr_output_info_get_display_name (Gde2RROutputInfo *self)
{
    g_return_val_if_fail (GDE2_IS_RR_OUTPUT_INFO (self), NULL);

    return self->priv->display_name;
}

gboolean gde2_rr_output_info_get_primary (Gde2RROutputInfo *self)
{
    g_return_val_if_fail (GDE2_IS_RR_OUTPUT_INFO (self), FALSE);

    return self->priv->primary;
}

void gde2_rr_output_info_set_primary (Gde2RROutputInfo *self, gboolean primary)
{
    g_return_if_fail (GDE2_IS_RR_OUTPUT_INFO (self));

    self->priv->primary = primary;
}

int gde2_rr_output_info_get_preferred_width (Gde2RROutputInfo *self)
{
    g_return_val_if_fail (GDE2_IS_RR_OUTPUT_INFO (self), 0);

    return self->priv->pref_width;
}

int gde2_rr_output_info_get_preferred_height (Gde2RROutputInfo *self)
{
    g_return_val_if_fail (GDE2_IS_RR_OUTPUT_INFO (self), 0);

    return self->priv->pref_height;
}
