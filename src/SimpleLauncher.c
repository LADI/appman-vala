#include <gtk/gtk.h>
#include "../build/rocketlauncher-0.1.h"

#define SPACE 40
#define ICON_SIZE 80


static gint screen_width;
static gint screen_height;

void set_widget_color(GtkWidget *widget, float red, float green, float blue, float opacity) {
	GdkRGBA bgcolor = {.0, .0, .1, 1.0}; //Default color
	if (red || green || blue || opacity) {
		bgcolor.red = red;
		bgcolor.green = green;
		bgcolor.blue = blue;
		bgcolor.alpha = opacity;
	}
	gtk_widget_override_background_color(widget, GTK_STATE_NORMAL, &bgcolor); //FIXME deprecated since GTK 3.16
}

gboolean resize_image(GtkWidget *widget, int width, int height) {
	GdkPixbuf *pixbuf =	gtk_image_get_pixbuf(GTK_IMAGE(widget));
	if (pixbuf == NULL)
	{
		g_printerr("Failed to resize image\n");
		return FALSE;
	}
	pixbuf = gdk_pixbuf_scale_simple(pixbuf, width, height, GDK_INTERP_BILINEAR);
	gtk_image_set_from_pixbuf(GTK_IMAGE(widget), pixbuf);
	return TRUE;
}

void resize_text(gchar* str, int limit) {
	if (strlen(str) > limit) {
		str[limit-2] = '.';
		str[limit-1] = '.';
		str[limit] = '\0';
	}
}

static gboolean on_icon_mouse_enter_callback (GtkWidget *widget, GdkEvent *event, gpointer data) {
    set_widget_color((GtkWidget*)data, 0.1, 0.5, .8, 1.0); //sky-blue
    return FALSE;
}


static gboolean on_icon_mouse_leave_callback (GtkWidget *widget, GdkEvent *event, gpointer data) {
    set_widget_color((GtkWidget*)data, 0, 0, 0, 0); //set default color
    return FALSE;
}

static gboolean on_icon_button_press_callback (GtkWidget *widget, GdkEventButton *event, gpointer data) {
	rocket_launcher_app_start((RocketLauncherApp*)data);
	gtk_main_quit ();
	return TRUE;
}

static gboolean on_window_key_press_callback (GtkSearchEntry *searchentry, GdkEvent *event, gpointer data)
{
	if (((GdkEventKey*)event)->keyval == GDK_KEY_Escape)
		gtk_main_quit ();
	return FALSE;
}

static gboolean on_search_entry_key_press_callback (GtkSearchEntry *searchentry, GdkEvent *event, gpointer data)
{
	//TODO finish here
	g_print("%c", ((GdkEventKey*)event)->keyval);
	return FALSE;
}

void add_applications(GtkGrid *grid) {
	int result = 0;
	int columns = screen_width/(SPACE+ICON_SIZE) - 2;
	RocketLauncherApplicationHandler *apphandl = rocket_launcher_application_handler_new ();
	RocketLauncherApp** apps = rocket_launcher_application_handler_get_apps (apphandl, &result);
	g_print ("Retrieved %d applications\n", result);
	g_print ("Columns: %d\n", columns);
	int j = 0;
	int t = result/columns;
	int i = 0;
	int x = 0;
	for (j = 0; j < columns; j++) gtk_grid_insert_column (grid, j);
	for (i=0; i < t; i++) {
		gtk_grid_insert_row (grid, i);
		for (j = 0; j < columns; j++) {
			GtkWidget *event_box = event_box = gtk_event_box_new ();
			GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
			GtkWidget *image = gtk_image_new_from_file (rocket_launcher_app_get_icon_path (apps[x]));
			resize_image(image, ICON_SIZE, ICON_SIZE);
			gtk_box_pack_start (GTK_BOX (box), image, FALSE, FALSE, 0);
			gchar *str = rocket_launcher_app_get_name (apps[x]);
			resize_text(str, 15);
			GtkWidget *label = gtk_label_new (NULL);
			gtk_label_set_markup (GTK_LABEL (label), g_strconcat("<span color='#FFFFFF'>",str,"</span>", NULL));
			g_free(str);
			gtk_box_pack_start (GTK_BOX (box), label, FALSE, FALSE, 0);
			gtk_container_add (GTK_CONTAINER (event_box), box);
			gtk_grid_attach(GTK_GRID(grid), event_box, j, i, 1, 1);
			g_signal_connect (G_OBJECT (event_box), "button-press-event", G_CALLBACK (on_icon_button_press_callback), (gpointer) apps[x]);
			g_signal_connect (G_OBJECT (event_box), "enter-notify-event", G_CALLBACK (on_icon_mouse_enter_callback), (gpointer) image);
			g_signal_connect (G_OBJECT (event_box), "leave-notify-event", G_CALLBACK (on_icon_mouse_leave_callback), (gpointer) image);
			x++;
		}
	}
}

int main (int argc, char **argv) {
	GtkWidget *window;
	
	gtk_init(&argc, &argv);
	
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	GdkRGBA bgcolor = {.0, .0, .0, 1.0};
	/* Get the size of the screen */
	GdkScreen *screen = gdk_screen_get_default ();
	screen_width = gdk_screen_get_width (screen);
	screen_height = gdk_screen_get_height (screen);
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
	GtkWidget *scrolled_window = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_min_content_height ((GtkScrolledWindow*)scrolled_window, screen_height-80 );
	GtkWidget *search_entry = gtk_search_entry_new ();
	gtk_widget_set_margin_start(search_entry, screen_width-800);
	gtk_widget_set_margin_end(search_entry, screen_width-800);
	gtk_widget_set_margin_top(search_entry, 20);
	gtk_box_pack_start (GTK_BOX (box), search_entry, FALSE, FALSE, 0);
	GtkWidget *grid = gtk_grid_new ();
	gtk_grid_set_row_spacing((GtkGrid*)grid, SPACE);
	gtk_grid_set_column_spacing((GtkGrid*)grid, SPACE);
	add_applications((GtkGrid*)grid);
	set_widget_color(window, 0, 0, 0, 0);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_window_fullscreen (GTK_WINDOW(window));
	gtk_window_set_modal(GTK_WINDOW(window), TRUE);
	
	gtk_container_add (GTK_CONTAINER(scrolled_window), grid);
	gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);
	gtk_box_pack_start (GTK_BOX (box), scrolled_window, FALSE, FALSE, 0);
	gtk_container_add (GTK_CONTAINER (window), box);
	
	gtk_widget_set_events(window, GDK_POINTER_MOTION_MASK);
	gtk_widget_set_events(window, GDK_BUTTON_PRESS_MASK);
	gtk_widget_set_events(scrolled_window, GDK_BUTTON_PRESS_MASK);

	g_signal_connect (G_OBJECT (window), "key-press-event", G_CALLBACK (on_window_key_press_callback), NULL);
	g_signal_connect (G_OBJECT (search_entry), "key-press-event", G_CALLBACK (on_search_entry_key_press_callback), NULL);

	gtk_widget_show_all (window);
	
	gtk_main ();

	return 0;
}