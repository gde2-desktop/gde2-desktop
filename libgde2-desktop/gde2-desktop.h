/*
 * gde2-desktop.h: general functions for libgde2-desktop
 *
 * Copyright (C) 2013 Stefano Karapetsas
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * Authors:
 *  Stefano Karapetsas <stefano@karapetsas.com>
 */

#ifndef __GDE2_DESKTOP_H__
#define __GDE2_DESKTOP_H__

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <glib.h>

G_BEGIN_DECLS

#define GDE2_DESKTOP_CHECK_VERSION(major,minor,micro) \
        (GDE2_MAJOR > (major) || \
        (GDE2_MAJOR == (major) && GDE2_MINOR > (minor)) || \
        (GDE2_MAJOR == (major) && GDE2_MINOR == (minor) && \
        GDE2_MICRO >= (micro)))

G_END_DECLS

#endif /* __GDE2_DESKTOP_H__ */
