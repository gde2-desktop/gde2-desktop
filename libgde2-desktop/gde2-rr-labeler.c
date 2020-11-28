/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * gde2-rr-labeler.c - Utility to label monitors to identify them
 * while they are being configured.
 *
 * Copyright 2008, Novell, Inc.
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
 * Boston, MA 02110-1301, USA.
 *
 * Author: Federico Mena-Quintero <federico@novell.com>
 */

#define GDE2_DESKTOP_USE_UNSTABLE_API

#include <config.h>
#include <glib/gi18n-lib.h>
#include <gtk/gtk.h>

#include <X11/Xproto.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <gdk/gdkx.h>

#include "gde2-rr-labeler.h"

struct _Gde2RRLabelerPrivate {
	Gde2RRConfig *config;

	int num_outputs;

#if GTK_CHECK_VERSION (3, 0, 0)
	GdkRGBA *palette;
#else
	GdkColor *palette;
#endif
	GtkWidget **windows;

	GdkScreen  *screen;
	Atom        workarea_atom;
};

enum {
	PROP_0,
	PROP_CONFIG,
	PROP_LAST
};

G_DEFINE_TYPE (Gde2RRLabeler, gde2_rr_labeler, G_TYPE_OBJECT);

static void gde2_rr_labeler_finalize (GObject *object);
static void create_label_windows (Gde2RRLabeler *labeler);
static void setup_from_config (Gde2RRLabeler *labeler);

static int
get_current_desktop (GdkScreen *screen)
{
        Display *display;
        Window win;
        Atom current_desktop, type;
        int format;
        unsigned long n_items, bytes_after;
        unsigned char *data_return = NULL;
        int workspace = 0;

        display = GDK_DISPLAY_XDISPLAY (gdk_screen_get_display (screen));
        win = XRootWindow (display, GDK_SCREEN_XNUMBER (screen));

        current_desktop = XInternAtom (display, "_NET_CURRENT_DESKTOP", True);

        XGetWindowProperty (display,
                            win,
                            current_desktop,
                            0, G_MAXLONG,
                            False, XA_CARDINAL,
                            &type, &format, &n_items, &bytes_after,
                            &data_return);

        if (type == XA_CARDINAL && format == 32 && n_items > 0)
                workspace = (int) data_return[0];
        if (data_return)
                XFree (data_return);

        return workspace;
}

static gboolean
get_work_area (Gde2RRLabeler *labeler,
	       GdkRectangle   *rect)
{
	Atom            workarea;
	Atom            type;
	Window          win;
	int             format;
	gulong          num;
	gulong          leftovers;
	gulong          max_len = 4 * 32;
	guchar         *ret_workarea;
	long           *workareas;
	int             result;
	int             disp_screen;
	int             desktop;
	Display        *display;

	display = GDK_DISPLAY_XDISPLAY (gdk_screen_get_display (labeler->priv->screen));
	workarea = XInternAtom (display, "_NET_WORKAREA", True);

	disp_screen = GDK_SCREEN_XNUMBER (labeler->priv->screen);

	/* Defaults in case of error */
	rect->x = 0;
	rect->y = 0;
	rect->width = gdk_screen_get_width (labeler->priv->screen);
	rect->height = gdk_screen_get_height (labeler->priv->screen);

	if (workarea == None)
		return FALSE;

	win = XRootWindow (display, disp_screen);
	result = XGetWindowProperty (display,
				     win,
				     workarea,
				     0,
				     max_len,
				     False,
				     AnyPropertyType,
				     &type,
				     &format,
				     &num,
				     &leftovers,
				     &ret_workarea);

	if (result != Success
	    || type == None
	    || format == 0
	    || leftovers
	    || num % 4) {
		return FALSE;
	}

	desktop = get_current_desktop (labeler->priv->screen);

	workareas = (long *) ret_workarea;
	rect->x = workareas[desktop * 4];
	rect->y = workareas[desktop * 4 + 1];
	rect->width = workareas[desktop * 4 + 2];
	rect->height = workareas[desktop * 4 + 3];

	XFree (ret_workarea);

	return TRUE;
}

static GdkFilterReturn
screen_xevent_filter (GdkXEvent      *xevent,
		      GdkEvent       *event,
		      Gde2RRLabeler *labeler)
{
	XEvent *xev;

	xev = (XEvent *) xevent;

	if (xev->type == PropertyNotify &&
	    xev->xproperty.atom == labeler->priv->workarea_atom) {
		/* update label positions */
		gde2_rr_labeler_hide (labeler);
		create_label_windows (labeler);
	}

	return GDK_FILTER_CONTINUE;
}

static void
gde2_rr_labeler_init (Gde2RRLabeler *labeler)
{
	GdkWindow *gdkwindow;

	labeler->priv = G_TYPE_INSTANCE_GET_PRIVATE (labeler, GDE2_TYPE_RR_LABELER, Gde2RRLabelerPrivate);

	labeler->priv->workarea_atom = XInternAtom (GDK_DISPLAY_XDISPLAY (gdk_display_get_default ()),
						    "_NET_WORKAREA",
						    True);

	labeler->priv->screen = gdk_screen_get_default ();
	/* code is not really designed to handle multiple screens so *shrug* */
	gdkwindow = gdk_screen_get_root_window (labeler->priv->screen);
	gdk_window_add_filter (gdkwindow, (GdkFilterFunc) screen_xevent_filter, labeler);
	gdk_window_set_events (gdkwindow, gdk_window_get_events (gdkwindow) | GDK_PROPERTY_CHANGE_MASK);
}

static void
gde2_rr_labeler_set_property (GObject *gobject, guint property_id, const GValue *value, GParamSpec *param_spec)
{
	Gde2RRLabeler *self = GDE2_RR_LABELER (gobject);

	switch (property_id) {
	case PROP_CONFIG:
		self->priv->config = GDE2_RR_CONFIG (g_value_dup_object (value));
		return;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (gobject, property_id, param_spec);
	}
}

static GObject *
gde2_rr_labeler_constructor (GType type, guint n_construct_properties, GObjectConstructParam *construct_properties)
{
	Gde2RRLabeler *self = (Gde2RRLabeler*) G_OBJECT_CLASS (gde2_rr_labeler_parent_class)->constructor (type, n_construct_properties, construct_properties);

	setup_from_config (self);

	return (GObject*) self;
}

static void
gde2_rr_labeler_class_init (Gde2RRLabelerClass *klass)
{
	GObjectClass *object_class;

	g_type_class_add_private (klass, sizeof (Gde2RRLabelerPrivate));

	object_class = (GObjectClass *) klass;

	object_class->set_property = gde2_rr_labeler_set_property;
	object_class->finalize = gde2_rr_labeler_finalize;
	object_class->constructor = gde2_rr_labeler_constructor;

	g_object_class_install_property (object_class, PROP_CONFIG, g_param_spec_object ("config",
											 "Configuration",
											 "RandR configuration to label",
											 GDE2_TYPE_RR_CONFIG,
											 G_PARAM_WRITABLE | G_PARAM_CONSTRUCT_ONLY |
											 G_PARAM_STATIC_NICK | G_PARAM_STATIC_BLURB));
}

static void
gde2_rr_labeler_finalize (GObject *object)
{
	Gde2RRLabeler *labeler;
	GdkWindow      *gdkwindow;

	labeler = GDE2_RR_LABELER (object);

	gdkwindow = gdk_screen_get_root_window (labeler->priv->screen);
	gdk_window_remove_filter (gdkwindow, (GdkFilterFunc) screen_xevent_filter, labeler);

	if (labeler->priv->config != NULL) {
		g_object_unref (labeler->priv->config);
	}

	if (labeler->priv->windows != NULL) {
		gde2_rr_labeler_hide (labeler);
		g_free (labeler->priv->windows);
	}

	g_free (labeler->priv->palette);

	G_OBJECT_CLASS (gde2_rr_labeler_parent_class)->finalize (object);
}

static int
count_outputs (Gde2RRConfig *config)
{
	int i;
	Gde2RROutputInfo **outputs = gde2_rr_config_get_outputs (config);

	for (i = 0; outputs[i] != NULL; i++)
		;

	return i;
}

static void
make_palette (Gde2RRLabeler *labeler)
{
	/* The idea is that we go around an hue color wheel.  We want to start
	 * at red, go around to green/etc. and stop at blue --- because magenta
	 * is evil.  Eeeeek, no magenta, please!
	 *
	 * Purple would be nice, though.  Remember that we are watered down
	 * (i.e. low saturation), so that would be like Like berries with cream.
	 * Mmmmm, berries.
	 */
	double start_hue;
	double end_hue;
	int i;

	g_assert (labeler->priv->num_outputs > 0);

#if GTK_CHECK_VERSION (3, 0, 0)
	labeler->priv->palette = g_new (GdkRGBA, labeler->priv->num_outputs);
#else
	labeler->priv->palette = g_new (GdkColor, labeler->priv->num_outputs);
#endif

	start_hue = 0.0; /* red */
	end_hue   = 2.0/3; /* blue */

	for (i = 0; i < labeler->priv->num_outputs; i++) {
		double h, s, v;
		double r, g, b;

		h = start_hue + (end_hue - start_hue) / labeler->priv->num_outputs * i;
		s = 1.0 / 3;
		v = 1.0;

		gtk_hsv_to_rgb (h, s, v, &r, &g, &b);

#if GTK_CHECK_VERSION (3, 0, 0)
		labeler->priv->palette[i].red   = r;
		labeler->priv->palette[i].green = g;
		labeler->priv->palette[i].blue  = b;
		labeler->priv->palette[i].alpha  = 1.0;
#else
		labeler->priv->palette[i].red   = (int) (65535 * r + 0.5);
		labeler->priv->palette[i].green = (int) (65535 * g + 0.5);
		labeler->priv->palette[i].blue  = (int) (65535 * b + 0.5);
#endif
	}
}

#define LABEL_WINDOW_EDGE_THICKNESS 2
#define LABEL_WINDOW_PADDING 12

static gboolean
#if GTK_CHECK_VERSION (3, 0, 0)
label_window_draw_event_cb (GtkWidget *widget, cairo_t *cr, gpointer data)
#else
label_window_expose_event_cb (GtkWidget *widget, GdkEventExpose *event, gpointer data)
#endif
{
#if GTK_CHECK_VERSION (3, 0, 0)
	GdkRGBA *color;
#else
	GdkColor *color;
#endif
	GtkAllocation allocation;

	color = g_object_get_data (G_OBJECT (widget), "color");
	gtk_widget_get_allocation (widget, &allocation);

#if !GTK_CHECK_VERSION (3, 0, 0)
	cairo_t *cr = gdk_cairo_create (gtk_widget_get_window (widget));
#endif

	/* edge outline */

	cairo_set_source_rgb (cr, 0, 0, 0);
	cairo_rectangle (cr,
			 LABEL_WINDOW_EDGE_THICKNESS / 2.0,
			 LABEL_WINDOW_EDGE_THICKNESS / 2.0,
			 allocation.width - LABEL_WINDOW_EDGE_THICKNESS,
			 allocation.height - LABEL_WINDOW_EDGE_THICKNESS);
	cairo_set_line_width (cr, LABEL_WINDOW_EDGE_THICKNESS);
	cairo_stroke (cr);

	/* fill */
#if GTK_CHECK_VERSION (3, 0, 0)
	gdk_cairo_set_source_rgba (cr, color);
#else
	gdk_cairo_set_source_color (cr, color);
#endif
	cairo_rectangle (cr,
			 LABEL_WINDOW_EDGE_THICKNESS,
			 LABEL_WINDOW_EDGE_THICKNESS,
			 allocation.width - LABEL_WINDOW_EDGE_THICKNESS * 2,
			 allocation.height - LABEL_WINDOW_EDGE_THICKNESS * 2);
	cairo_fill (cr);

#if !GTK_CHECK_VERSION (3, 0, 0)
	cairo_destroy (cr);
#endif

	return FALSE;
}

static void
position_window (Gde2RRLabeler  *labeler,
		 GtkWidget       *window,
		 int              x,
		 int              y)
{
	GdkRectangle    workarea;
	GdkRectangle    monitor;
	int             monitor_num;

	get_work_area (labeler, &workarea);
	monitor_num = gdk_screen_get_monitor_at_point (labeler->priv->screen, x, y);
	gdk_screen_get_monitor_geometry (labeler->priv->screen,
                                         monitor_num,
                                         &monitor);
	gdk_rectangle_intersect (&monitor, &workarea, &workarea);

	gtk_window_move (GTK_WINDOW (window), workarea.x, workarea.y);
}

#if GTK_CHECK_VERSION (3, 0, 0)
static GtkWidget *
create_label_window (Gde2RRLabeler *labeler, Gde2RROutputInfo *output, GdkRGBA *color)
#else
static GtkWidget *
create_label_window (Gde2RRLabeler *labeler, Gde2RROutputInfo *output, GdkColor *color)
#endif
{
	GtkWidget *window;
	GtkWidget *widget;
	char *str;
	char *display_name;
	GdkColor black = { 0, 0, 0, 0 };
	int x,y;

	window = gtk_window_new (GTK_WINDOW_POPUP);
	gtk_widget_set_app_paintable (window, TRUE);

	gtk_container_set_border_width (GTK_CONTAINER (window), LABEL_WINDOW_PADDING + LABEL_WINDOW_EDGE_THICKNESS);

	/* This is semi-dangerous.  The color is part of the labeler->palette
	 * array.  Note that in gde2_rr_labeler_finalize(), we are careful to
	 * free the palette only after we free the windows.
	 */
	g_object_set_data (G_OBJECT (window), "color", color);

#if GTK_CHECK_VERSION (3, 0, 0)
	g_signal_connect (window, "draw",
			  G_CALLBACK (label_window_draw_event_cb), labeler);
#else
	g_signal_connect (window, "expose-event",
			  G_CALLBACK (label_window_expose_event_cb), labeler);
#endif

	if (gde2_rr_config_get_clone (labeler->priv->config)) {
		/* Keep this string in sync with gde2-control-center/capplets/display/xrandr-capplet.c:get_display_name() */

		/* Translators:  this is the feature where what you see on your laptop's
		 * screen is the same as your external monitor.  Here, "Mirror" is being
		 * used as an adjective, not as a verb.  For example, the Spanish
		 * translation could be "Pantallas en Espejo", *not* "Espejar Pantallas".
		 */
		display_name = g_strdup_printf (_("Mirror Screens"));
		str = g_strdup_printf ("<b>%s</b>", display_name);
	} else {
		display_name = g_strdup_printf ("<b>%s</b>\n<small>%s</small>", gde2_rr_output_info_get_display_name (output), gde2_rr_output_info_get_name (output));
		str = g_strdup_printf ("%s", display_name);
	}
	g_free (display_name);

	widget = gtk_label_new (NULL);
	gtk_label_set_markup (GTK_LABEL (widget), str);
	g_free (str);

	/* Make the label explicitly black.  We don't want it to follow the
	 * theme's colors, since the label is always shown against a light
	 * pastel background.  See bgo#556050
	 */
#if GTK_CHECK_VERSION(3,0,0)
	gtk_widget_modify_fg (widget, gtk_widget_get_state_flags (widget), &black);
#else
	gtk_widget_modify_fg (widget, gtk_widget_get_state (widget), &black);
#endif

	gtk_container_add (GTK_CONTAINER (window), widget);

	/* Should we center this at the top edge of the monitor, instead of using the upper-left corner? */
	gde2_rr_output_info_get_geometry (output, &x, &y, NULL, NULL);
	position_window (labeler, window, x, y);

	gtk_widget_show_all (window);

	return window;
}

static void
create_label_windows (Gde2RRLabeler *labeler)
{
	int i;
	gboolean created_window_for_clone;
	Gde2RROutputInfo **outputs;

	labeler->priv->windows = g_new (GtkWidget *, labeler->priv->num_outputs);

	created_window_for_clone = FALSE;

	outputs = gde2_rr_config_get_outputs (labeler->priv->config);

	for (i = 0; i < labeler->priv->num_outputs; i++) {
		if (!created_window_for_clone && gde2_rr_output_info_is_active (outputs[i])) {
			labeler->priv->windows[i] = create_label_window (labeler, outputs[i], labeler->priv->palette + i);

			if (gde2_rr_config_get_clone (labeler->priv->config))
				created_window_for_clone = TRUE;
		} else
			labeler->priv->windows[i] = NULL;
	}
}

static void
setup_from_config (Gde2RRLabeler *labeler)
{
	labeler->priv->num_outputs = count_outputs (labeler->priv->config);

	make_palette (labeler);

	create_label_windows (labeler);
}

/**
 * gde2_rr_labeler_new:
 * @config: Configuration of the screens to label
 *
 * Create a GUI element that will display colored labels on each connected monitor.
 * This is useful when users are required to identify which monitor is which, e.g. for
 * for configuring multiple monitors.
 * The labels will be shown by default, use gde2_rr_labeler_hide to hide them.
 *
 * Returns: A new #Gde2RRLabeler
 */
Gde2RRLabeler *
gde2_rr_labeler_new (Gde2RRConfig *config)
{
	g_return_val_if_fail (GDE2_IS_RR_CONFIG (config), NULL);

	return g_object_new (GDE2_TYPE_RR_LABELER, "config", config, NULL);
}

/**
 * gde2_rr_labeler_hide:
 * @labeler: A #Gde2RRLabeler
 *
 * Hide ouput labels.
 */
void
gde2_rr_labeler_hide (Gde2RRLabeler *labeler)
{
	int i;
	Gde2RRLabelerPrivate *priv;

	g_return_if_fail (GDE2_IS_RR_LABELER (labeler));

	priv = labeler->priv;

	if (priv->windows == NULL)
		return;

	for (i = 0; i < priv->num_outputs; i++)
		if (priv->windows[i] != NULL) {
			gtk_widget_destroy (priv->windows[i]);
			priv->windows[i] = NULL;
	}
	g_free (priv->windows);
	priv->windows = NULL;
}

#if GTK_CHECK_VERSION (3, 0, 0)
/**
 * gde2_rr_labeler_get_rgba_for_output:
 * @labeler: A #Gde2RRLabeler
 * @output: Output device (i.e. monitor) to query
 * @rgba_out: (out): Color of selected monitor.
 *
 * Get the color used for the label on a given output (monitor).
 */
void
gde2_rr_labeler_get_rgba_for_output (Gde2RRLabeler *labeler, Gde2RROutputInfo *output, GdkRGBA *color_out)
{
	int i;
	Gde2RROutputInfo **outputs;

	g_return_if_fail (GDE2_IS_RR_LABELER (labeler));
	g_return_if_fail (GDE2_IS_RR_OUTPUT_INFO (output));
	g_return_if_fail (color_out != NULL);

	outputs = gde2_rr_config_get_outputs (labeler->priv->config);

	for (i = 0; i < labeler->priv->num_outputs; i++)
		if (outputs[i] == output) {
			*color_out = labeler->priv->palette[i];
			return;
		}

	g_warning ("trying to get the color for unknown Gde2OutputInfo %p; returning magenta!", output);

	color_out->red   = 1.0;
	color_out->green = 0.0;
	color_out->blue  = 1.0;
	color_out->alpha = 1.0;
}
#endif

/**
 * gde2_rr_labeler_get_color_for_output:
 * @labeler: A #Gde2RRLabeler
 * @output: Output device (i.e. monitor) to query
 * @color_out: (out): Color of selected monitor.
 *
 * Get the color used for the label on a given output (monitor).
 */
void
gde2_rr_labeler_get_color_for_output (Gde2RRLabeler *labeler, Gde2RROutputInfo *output, GdkColor *color_out)
{
	int i;
	Gde2RROutputInfo **outputs;

	g_return_if_fail (GDE2_IS_RR_LABELER (labeler));
	g_return_if_fail (GDE2_IS_RR_OUTPUT_INFO (output));
	g_return_if_fail (color_out != NULL);

	outputs = gde2_rr_config_get_outputs (labeler->priv->config);

	for (i = 0; i < labeler->priv->num_outputs; i++)
		if (outputs[i] == output) {
#if GTK_CHECK_VERSION (3, 0, 0)
			color_out->red = labeler->priv->palette[i].red * 0xffff;
			color_out->green = labeler->priv->palette[i].green * 0xffff;
			color_out->blue = labeler->priv->palette[i].blue * 0xffff;
#else
			*color_out = labeler->priv->palette[i];
#endif
			return;
		}

	g_warning ("trying to get the color for unknown Gde2OutputInfo %p; returning magenta!", output);

	color_out->red   = 0xffff;
	color_out->green = 0;
	color_out->blue  = 0xffff;
}
