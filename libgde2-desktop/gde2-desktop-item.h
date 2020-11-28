/* -*- Mode: C; c-set-style: linux indent-tabs-mode: t; c-basic-offset: 8; tab-width: 8 -*- */
/* gde2-ditem.h - GDE2 Desktop File Representation

   Copyright (C) 1999, 2000 Red Hat Inc.
   Copyright (C) 2001 Sid Vicious
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

#ifndef GDE2_DITEM_H
#define GDE2_DITEM_H

#include <glib.h>
#include <glib-object.h>

#include <gdk/gdk.h>
#include <gtk/gtk.h>

G_BEGIN_DECLS

typedef enum {
	GDE2_DESKTOP_ITEM_TYPE_NULL = 0 /* This means its NULL, that is, not
					   * set */,
	GDE2_DESKTOP_ITEM_TYPE_OTHER /* This means it's not one of the below
					      strings types, and you must get the
					      Type attribute. */,

	/* These are the standard compliant types: */
	GDE2_DESKTOP_ITEM_TYPE_APPLICATION,
	GDE2_DESKTOP_ITEM_TYPE_LINK,
	GDE2_DESKTOP_ITEM_TYPE_FSDEVICE,
	GDE2_DESKTOP_ITEM_TYPE_MIME_TYPE,
	GDE2_DESKTOP_ITEM_TYPE_DIRECTORY,
	GDE2_DESKTOP_ITEM_TYPE_SERVICE,
	GDE2_DESKTOP_ITEM_TYPE_SERVICE_TYPE
} Gde2DesktopItemType;

typedef enum {
        GDE2_DESKTOP_ITEM_UNCHANGED = 0,
        GDE2_DESKTOP_ITEM_CHANGED = 1,
        GDE2_DESKTOP_ITEM_DISAPPEARED = 2
} Gde2DesktopItemStatus;

#define GDE2_TYPE_DESKTOP_ITEM         (gde2_desktop_item_get_type ())
GType gde2_desktop_item_get_type       (void);

typedef struct _Gde2DesktopItem Gde2DesktopItem;

/* standard */
#define GDE2_DESKTOP_ITEM_ENCODING	"Encoding" /* string */
#define GDE2_DESKTOP_ITEM_VERSION	"Version"  /* numeric */
#define GDE2_DESKTOP_ITEM_NAME		"Name" /* localestring */
#define GDE2_DESKTOP_ITEM_GENERIC_NAME	"GenericName" /* localestring */
#define GDE2_DESKTOP_ITEM_TYPE		"Type" /* string */
#define GDE2_DESKTOP_ITEM_FILE_PATTERN "FilePattern" /* regexp(s) */
#define GDE2_DESKTOP_ITEM_TRY_EXEC	"TryExec" /* string */
#define GDE2_DESKTOP_ITEM_NO_DISPLAY	"NoDisplay" /* boolean */
#define GDE2_DESKTOP_ITEM_COMMENT	"Comment" /* localestring */
#define GDE2_DESKTOP_ITEM_EXEC		"Exec" /* string */
#define GDE2_DESKTOP_ITEM_ACTIONS	"Actions" /* strings */
#define GDE2_DESKTOP_ITEM_ICON		"Icon" /* string */
#define GDE2_DESKTOP_ITEM_MINI_ICON	"MiniIcon" /* string */
#define GDE2_DESKTOP_ITEM_HIDDEN	"Hidden" /* boolean */
#define GDE2_DESKTOP_ITEM_PATH		"Path" /* string */
#define GDE2_DESKTOP_ITEM_TERMINAL	"Terminal" /* boolean */
#define GDE2_DESKTOP_ITEM_TERMINAL_OPTIONS "TerminalOptions" /* string */
#define GDE2_DESKTOP_ITEM_SWALLOW_TITLE "SwallowTitle" /* string */
#define GDE2_DESKTOP_ITEM_SWALLOW_EXEC	"SwallowExec" /* string */
#define GDE2_DESKTOP_ITEM_MIME_TYPE	"MimeType" /* regexp(s) */
#define GDE2_DESKTOP_ITEM_PATTERNS	"Patterns" /* regexp(s) */
#define GDE2_DESKTOP_ITEM_DEFAULT_APP	"DefaultApp" /* string */
#define GDE2_DESKTOP_ITEM_DEV		"Dev" /* string */
#define GDE2_DESKTOP_ITEM_FS_TYPE	"FSType" /* string */
#define GDE2_DESKTOP_ITEM_MOUNT_POINT	"MountPoint" /* string */
#define GDE2_DESKTOP_ITEM_READ_ONLY	"ReadOnly" /* boolean */
#define GDE2_DESKTOP_ITEM_UNMOUNT_ICON "UnmountIcon" /* string */
#define GDE2_DESKTOP_ITEM_SORT_ORDER	"SortOrder" /* strings */
#define GDE2_DESKTOP_ITEM_URL		"URL" /* string */
#define GDE2_DESKTOP_ITEM_DOC_PATH	"X-GDE2-DocPath" /* string */

/* The vfolder proposal */
#define GDE2_DESKTOP_ITEM_CATEGORIES	"Categories" /* string */
#define GDE2_DESKTOP_ITEM_ONLY_SHOW_IN	"OnlyShowIn" /* string */

typedef enum {
	/* Use the TryExec field to determine if this should be loaded */
        GDE2_DESKTOP_ITEM_LOAD_ONLY_IF_EXISTS = 1<<0,
        GDE2_DESKTOP_ITEM_LOAD_NO_TRANSLATIONS = 1<<1
} Gde2DesktopItemLoadFlags;

typedef enum {
	/* Never launch more instances even if the app can only
	 * handle one file and we have passed many */
        GDE2_DESKTOP_ITEM_LAUNCH_ONLY_ONE = 1<<0,
	/* Use current directory instead of home directory */
        GDE2_DESKTOP_ITEM_LAUNCH_USE_CURRENT_DIR = 1<<1,
	/* Append the list of URIs to the command if no Exec
	 * parameter is specified, instead of launching the
	 * app without parameters. */
	GDE2_DESKTOP_ITEM_LAUNCH_APPEND_URIS = 1<<2,
	/* Same as above but instead append local paths */
	GDE2_DESKTOP_ITEM_LAUNCH_APPEND_PATHS = 1<<3,
	/* Don't automatically reap child process.  */
	GDE2_DESKTOP_ITEM_LAUNCH_DO_NOT_REAP_CHILD = 1<<4
} Gde2DesktopItemLaunchFlags;

typedef enum {
	/* Don't check the kde directories */
        GDE2_DESKTOP_ITEM_ICON_NO_KDE = 1<<0
} Gde2DesktopItemIconFlags;

typedef enum {
	GDE2_DESKTOP_ITEM_ERROR_NO_FILENAME /* No filename set or given on save */,
	GDE2_DESKTOP_ITEM_ERROR_UNKNOWN_ENCODING /* Unknown encoding of the file */,
	GDE2_DESKTOP_ITEM_ERROR_CANNOT_OPEN /* Cannot open file */,
	GDE2_DESKTOP_ITEM_ERROR_NO_EXEC_STRING /* Cannot launch due to no execute string */,
	GDE2_DESKTOP_ITEM_ERROR_BAD_EXEC_STRING /* Cannot launch due to bad execute string */,
	GDE2_DESKTOP_ITEM_ERROR_NO_URL /* No URL on a url entry*/,
	GDE2_DESKTOP_ITEM_ERROR_NOT_LAUNCHABLE /* Not a launchable type of item */,
	GDE2_DESKTOP_ITEM_ERROR_INVALID_TYPE /* Not of type application/x-gde2-app-info */
} Gde2DesktopItemError;

/* Note that functions can also return the G_FILE_ERROR_* errors */

#define GDE2_DESKTOP_ITEM_ERROR gde2_desktop_item_error_quark ()
GQuark gde2_desktop_item_error_quark (void);

/* Returned item from new*() and copy() methods have a refcount of 1 */
Gde2DesktopItem *      gde2_desktop_item_new               (void);
Gde2DesktopItem *      gde2_desktop_item_new_from_file     (const char                 *file,
							      Gde2DesktopItemLoadFlags   flags,
							      GError                    **error);
Gde2DesktopItem *      gde2_desktop_item_new_from_uri      (const char                 *uri,
							      Gde2DesktopItemLoadFlags   flags,
							      GError                    **error);
Gde2DesktopItem *      gde2_desktop_item_new_from_string   (const char                 *uri,
							      const char                 *string,
							      gssize                      length,
							      Gde2DesktopItemLoadFlags   flags,
							      GError                    **error);
Gde2DesktopItem *      gde2_desktop_item_new_from_basename (const char                 *basename,
							      Gde2DesktopItemLoadFlags   flags,
							      GError                    **error);
Gde2DesktopItem *      gde2_desktop_item_copy              (const Gde2DesktopItem     *item);

/* if under is NULL save in original location */
gboolean                gde2_desktop_item_save              (Gde2DesktopItem           *item,
							      const char                 *under,
							      gboolean			  force,
							      GError                    **error);
Gde2DesktopItem *      gde2_desktop_item_ref               (Gde2DesktopItem           *item);
void                    gde2_desktop_item_unref             (Gde2DesktopItem           *item);
int			gde2_desktop_item_launch	     (const Gde2DesktopItem     *item,
							      GList                      *file_list,
							      Gde2DesktopItemLaunchFlags flags,
							      GError                    **error);
int			gde2_desktop_item_launch_with_env   (const Gde2DesktopItem     *item,
							      GList                      *file_list,
							      Gde2DesktopItemLaunchFlags flags,
							      char                      **envp,
							      GError                    **error);

int                     gde2_desktop_item_launch_on_screen  (const Gde2DesktopItem       *item,
							      GList                        *file_list,
							      Gde2DesktopItemLaunchFlags   flags,
							      GdkScreen                    *screen,
							      int                           workspace,
							      GError                      **error);

/* A list of files or urls dropped onto an icon */
int                     gde2_desktop_item_drop_uri_list     (const Gde2DesktopItem     *item,
							      const char                 *uri_list,
							      Gde2DesktopItemLaunchFlags flags,
							      GError                    **error);

int                     gde2_desktop_item_drop_uri_list_with_env    (const Gde2DesktopItem     *item,
								      const char                 *uri_list,
								      Gde2DesktopItemLaunchFlags flags,
								      char                      **envp,
								      GError                    **error);

gboolean                gde2_desktop_item_exists            (const Gde2DesktopItem     *item);

Gde2DesktopItemType	gde2_desktop_item_get_entry_type    (const Gde2DesktopItem	 *item);
/* You could also just use the set_string on the TYPE argument */
void			gde2_desktop_item_set_entry_type    (Gde2DesktopItem		 *item,
							      Gde2DesktopItemType	  type);

/* Get current location on disk */
const char *            gde2_desktop_item_get_location      (const Gde2DesktopItem     *item);
void                    gde2_desktop_item_set_location      (Gde2DesktopItem           *item,
							      const char                 *location);
void                    gde2_desktop_item_set_location_file (Gde2DesktopItem           *item,
							      const char                 *file);
Gde2DesktopItemStatus  gde2_desktop_item_get_file_status   (const Gde2DesktopItem     *item);

/*
 * Get the icon, this is not as simple as getting the Icon attr as it actually tries to find
 * it and returns %NULL if it can't
 */
char *                  gde2_desktop_item_get_icon          (const Gde2DesktopItem     *item,
							      GtkIconTheme               *icon_theme);

char *                  gde2_desktop_item_find_icon         (GtkIconTheme               *icon_theme,
							      const char                 *icon,
							      /* size is only a suggestion */
							      int                         desired_size,
							      int                         flags);


/*
 * Reading/Writing different sections, NULL is the standard section
 */
gboolean                gde2_desktop_item_attr_exists       (const Gde2DesktopItem     *item,
							      const char                 *attr);

/*
 * String type
 */
const char *            gde2_desktop_item_get_string        (const Gde2DesktopItem     *item,
							      const char		 *attr);

void                    gde2_desktop_item_set_string        (Gde2DesktopItem           *item,
							      const char		 *attr,
							      const char                 *value);

const char *            gde2_desktop_item_get_attr_locale   (const Gde2DesktopItem     *item,
							      const char		 *attr);

/*
 * LocaleString type
 */
const char *            gde2_desktop_item_get_localestring  (const Gde2DesktopItem     *item,
							      const char		 *attr);
const char *            gde2_desktop_item_get_localestring_lang (const Gde2DesktopItem *item,
								  const char		 *attr,
								  const char             *language);
/* use g_list_free only */
GList *                 gde2_desktop_item_get_languages     (const Gde2DesktopItem     *item,
							      const char		 *attr);

void                    gde2_desktop_item_set_localestring  (Gde2DesktopItem           *item,
							      const char		 *attr,
							      const char                 *value);
void                    gde2_desktop_item_set_localestring_lang  (Gde2DesktopItem      *item,
								   const char		 *attr,
								   const char		 *language,
								   const char            *value);
void                    gde2_desktop_item_clear_localestring(Gde2DesktopItem           *item,
							      const char		 *attr);

/*
 * Strings, Regexps types
 */

/* use gde2_desktop_item_free_string_list */
char **                 gde2_desktop_item_get_strings       (const Gde2DesktopItem     *item,
							      const char		 *attr);

void			gde2_desktop_item_set_strings       (Gde2DesktopItem           *item,
							      const char                 *attr,
							      char                      **strings);

/*
 * Boolean type
 */
gboolean                gde2_desktop_item_get_boolean       (const Gde2DesktopItem     *item,
							      const char		 *attr);

void                    gde2_desktop_item_set_boolean       (Gde2DesktopItem           *item,
							      const char		 *attr,
							      gboolean                    value);

/*
 * Xserver time of user action that caused the application launch to start.
 */
void                    gde2_desktop_item_set_launch_time   (Gde2DesktopItem           *item,
							      guint32                     timestamp);

/*
 * Clearing attributes
 */
#define                 gde2_desktop_item_clear_attr(item,attr) \
				gde2_desktop_item_set_string(item,attr,NULL)
void			gde2_desktop_item_clear_section     (Gde2DesktopItem           *item,
							      const char                 *section);

G_END_DECLS

#endif /* GDE2_DITEM_H */
