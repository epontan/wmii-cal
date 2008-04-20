/* wmii-cal - calendar for wmii
 *
 * Copyright 2008 Pontus Andersson
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <X11/Xlib.h>
#include <gtk/gtk.h>

int get_wmii_offset(Display *dpy, const char *font) {
    XFontStruct *xfont;

	if(font && font[0] != '\0' && (xfont = XLoadQueryFont(dpy, font))) {
        return xfont->ascent + xfont->descent + 2;
    }
    else {
        return 0;
    }
}

void cb_month_changed(GtkWidget *calendar)
{
    time_t timer;
    struct tm *tm;
    guint year, month;

    timer = time(NULL);
    tm = localtime(&timer);

    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, NULL);

    gtk_calendar_clear_marks(GTK_CALENDAR(calendar));
    if(tm->tm_year == (year-1900) && tm->tm_mon == month)
        gtk_calendar_mark_day(GTK_CALENDAR(calendar), tm->tm_mday);	
}

void setup_widgets(int x, int y)
{
    GtkWidget *window, *vbox, *calendar, *button;
    gint options_mask, width, height;

    options_mask = GTK_CALENDAR_SHOW_HEADING |
                   GTK_CALENDAR_SHOW_DAY_NAMES |
                   GTK_CALENDAR_SHOW_WEEK_NUMBERS;

    window = gtk_window_new(GTK_WINDOW_POPUP);
    g_signal_connect(G_OBJECT(window), "destroy",
            G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);

    vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    calendar=gtk_calendar_new();
    gtk_calendar_set_display_options(GTK_CALENDAR(calendar), options_mask);
    g_signal_connect(G_OBJECT(calendar), "month_changed", 
            G_CALLBACK(cb_month_changed), NULL);
    cb_month_changed(calendar);
    gtk_container_add(GTK_CONTAINER(vbox), calendar);

    button = gtk_button_new_with_label("Close");
    g_signal_connect(G_OBJECT(button), "clicked", 
            G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add(GTK_CONTAINER(vbox), button);
    GTK_WIDGET_SET_FLAGS(button, GTK_CAN_DEFAULT);
    gtk_widget_grab_default(button);

    gtk_window_move(GTK_WINDOW(window), x , y); /* move outside */
    gtk_widget_show_all(window);

    gtk_window_get_size(GTK_WINDOW(window), &width, &height);
    gtk_window_move(GTK_WINDOW(window), x-width , y-height);
}

int main(int argc, char **argv)
{
    Display *dpy;
    char *font;
    int width, height;
    int i;

    dpy = XOpenDisplay(getenv("DISPLAY"));
    font = NULL;
    width = DisplayWidth(dpy, DefaultScreen(dpy));
    height = DisplayHeight(dpy, DefaultScreen(dpy));

    for(i = 1; i < argc; i++)
        if(!strcmp(argv[i], "-fn")) {
            if(++i < argc) font = argv[i];
        }
        else if(!strcmp(argv[i], "-v")) {
			printf("wmii-cal-1.0, © 2008 Pontus Andersson\n");
            exit(EXIT_SUCCESS);
        }
        else if(!strcmp(argv[i], "-h")) {
			printf("usage: wmii-cal [-fn <wmii_font>]\n");
            exit(EXIT_SUCCESS);
        }    

    gtk_init(&argc, &argv);
    setup_widgets(width, height - get_wmii_offset(dpy, font));
    gtk_main();

    return EXIT_SUCCESS;
}
