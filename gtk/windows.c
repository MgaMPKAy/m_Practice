#include <gtk/gtk.h>
#include <stdlib.h>

int main(int argc, char *argv[]);

void new_popup(GtkWidget *widget, gpointer *data)
{
	GtkWidget *popup;
	GtkWidget *button;
	static gboolean flag = TRUE;
	if ((flag = !flag)) {
		popup = gtk_window_new(GTK_WINDOW_POPUP);
		button = gtk_button_new_with_label("A Popup");
	} else {
		popup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		button = gtk_button_new_with_label("A Toplevel");
	}
	gtk_window_set_position(GTK_WINDOW(popup), GTK_WIN_POS_MOUSE);
	
	g_signal_connect_swapped(G_OBJECT(button),"clicked",
				 G_CALLBACK(gtk_widget_destroy), popup);
	gtk_container_add(GTK_CONTAINER(popup), button);
	gtk_widget_show_all(popup);
}

int main(int argc, char *argv[])
{
	GtkWidget *window;
	GtkWidget *vbox;
	gtk_init(&argc, &argv);
	
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_MOUSE);
	gtk_window_set_decorated(GTK_WINDOW(window), FALSE);
	gtk_window_set_title(GTK_WINDOW(window), "Main Window");
	gtk_window_begin_move_drag(GTK_WINDOW(window), 1,
				   398, 198, 10);
				   
	g_signal_connect(G_OBJECT(window), "destroy",
			 G_CALLBACK(main), NULL);
	
	
	vbox = gtk_vbox_new(TRUE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);
	
	GtkWidget *button_popup = gtk_button_new_with_label("Popup?");
	gtk_box_pack_start(GTK_BOX(vbox), button_popup, TRUE, TRUE, 0);
	g_signal_connect(G_OBJECT(button_popup), "clicked",
			 G_CALLBACK(new_popup), NULL);
	
	
	GtkWidget *button_main = gtk_button_new_from_stock(GTK_STOCK_NEW);
	gtk_box_pack_start(GTK_BOX(vbox), button_main, TRUE, TRUE, 0);
	g_signal_connect(G_OBJECT(button_main), "clicked",
			 G_CALLBACK(main), NULL);
		
	GtkWidget *button_quit = gtk_button_new_from_stock(GTK_STOCK_QUIT);
	gtk_box_pack_start(GTK_BOX(vbox), button_quit, TRUE, TRUE, 0);
	g_signal_connect_swapped(G_OBJECT(button_quit), "clicked",
				 G_CALLBACK(exit), GINT_TO_POINTER(0));

	GtkWidget *button_iconify = gtk_button_new_with_label("Iconify (Minimize)");
	gtk_box_pack_start(GTK_BOX(vbox), button_iconify, FALSE, FALSE, 0);
	g_signal_connect_swapped(G_OBJECT(button_iconify), "clicked",
				 G_CALLBACK(gtk_window_iconify), window);
		
	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}
