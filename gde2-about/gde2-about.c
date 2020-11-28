/* -*- Mode: C; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
 *
 * Copyright (C) 2011 Perberos <perberos@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "gde2-about.h"

/* get text macro, this should be on the common macros. or not?
 */
#ifndef gde2_gettext
#define gde2_gettext(package, locale, codeset) \
    bindtextdomain(package, locale); \
    bind_textdomain_codeset(package, codeset); \
    textdomain(package);
#endif

#if GTK_CHECK_VERSION(3, 0, 0)

static void gde2_about_on_activate(GtkApplication* app)
{
    GList* list;
    GtkWidget* window;

    list = gtk_application_get_windows(app);

    if (list)
    {
        gtk_window_present(GTK_WINDOW(list->data));
    }
    else
    {
        gde2_about_run();
    }
}

#else

// callback
static void gde2_about_on_activate(GApplication* app)
{
    if (!gde2_about_dialog)
    {
        gde2_about_run();
    }
    else
    {
        gtk_window_present(GTK_WINDOW(gde2_about_dialog));
    }
}

#endif

void gde2_about_run(void)
{
    gde2_about_dialog = (Gde2AboutDialog*) gde2_about_dialog_new();

    gtk_window_set_default_icon_name(icon);
    gde2_about_dialog_set_logo_icon_name(gde2_about_dialog, icon);

    // name
    gde2_about_dialog_set_program_name(gde2_about_dialog, gettext(program_name));

    // version
    gde2_about_dialog_set_version(gde2_about_dialog, version);

    // credits and website
    gde2_about_dialog_set_copyright(gde2_about_dialog, copyright);
    gde2_about_dialog_set_website(gde2_about_dialog, website);

    /**
     * This generate a random message.
     * The comments index must not be more than comments_count - 1
     */
    gde2_about_dialog_set_comments(gde2_about_dialog, gettext(comments_array[g_random_int_range(0, comments_count - 1)]));

    gde2_about_dialog_set_authors(gde2_about_dialog, authors);
    gde2_about_dialog_set_artists(gde2_about_dialog, artists);
    gde2_about_dialog_set_documenters(gde2_about_dialog, documenters);
    /* Translators should localize the following string which will be
     * displayed in the about box to give credit to the translator(s). */
    gde2_about_dialog_set_translator_credits(gde2_about_dialog, _("translator-credits"));

    #if GTK_CHECK_VERSION(3, 0, 0)
        gtk_window_set_application(GTK_WINDOW(gde2_about_dialog), gde2_about_application);
    #endif

    // start and destroy
    gtk_dialog_run((GtkDialog*) gde2_about_dialog);
    gtk_widget_destroy((GtkWidget*) gde2_about_dialog);
}

int main(int argc, char** argv)
{
    int status = 0;

    gde2_gettext(GETTEXT_PACKAGE, LOCALE_DIR, "UTF-8");

    /* http://www.gtk.org/api/2.6/glib/glib-Commandline-option-parser.html */
    GOptionContext* context = g_option_context_new(NULL);
    g_option_context_add_main_entries(context, command_entries, GETTEXT_PACKAGE);
    g_option_context_add_group(context, gtk_get_option_group(TRUE));
    g_option_context_parse(context, &argc, &argv, NULL);

    /* Not necesary at all, program just run and die.
     * But it free a little memory. */
    g_option_context_free(context);

    if (gde2_about_nogui == TRUE)
    {
        printf("%s %s\n", gettext(program_name), version);
    }
    else
    {
        gtk_init(&argc, &argv);

        #if GTK_CHECK_VERSION(3, 0, 0)

            gde2_about_application = gtk_application_new("org.gde2.about", 0);
            g_signal_connect(gde2_about_application, "activate", G_CALLBACK(gde2_about_on_activate), NULL);

            status = g_application_run(G_APPLICATION(gde2_about_application), argc, argv);

            g_object_unref(gde2_about_application);

        #else

            gde2_about_application = g_application_new("org.gde2.about", G_APPLICATION_FLAGS_NONE);
            g_signal_connect(gde2_about_application, "activate", G_CALLBACK(gde2_about_on_activate), NULL);

            status = g_application_run(G_APPLICATION(gde2_about_application), argc, argv);

            g_object_unref(gde2_about_application);

        #endif
    }

    return status;
}
