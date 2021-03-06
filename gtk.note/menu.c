
/* 
 * gcc -o simple menu.c `pkg-config --libs --cflags gtk+-2.0`
 *
 * Menu widget Demonstration
 *
 * */
#include <gtk/gtk.h>


int main( int argc, char *argv[])
{

	GtkWidget *window;
	GtkWidget *vbox;

	GtkWidget *menubar;
	GtkWidget *filemenu;
	GtkWidget *file;
	GtkWidget *quit;

	gtk_init(&argc, &argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 250, 200);
	gtk_window_set_title(GTK_WINDOW(window), "menu");

	vbox = gtk_vbox_new(FALSE, 0);
	gtk_container_add(GTK_CONTAINER(window), vbox);

	// menu bar and menu are both subclass of GtkMenuShell class
	// menu bar is used to contain one or more menu items
	// menu is used to implement submenu (drop down menu) or pop up menu
	menubar = gtk_menu_bar_new();
	filemenu = gtk_menu_new();

	// file is the root menu item
	file = gtk_menu_item_new_with_label("File");
	quit = gtk_menu_item_new_with_label("Quit");

	// attaches a submenu to the root menu item
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(file), filemenu);
	
	// append a menu item to the menu (submenu)
	gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quit);

	// append a menu item to the menu bar
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar), file);

	gtk_box_pack_start(GTK_BOX(vbox), menubar, FALSE, FALSE, 3);

	g_signal_connect_swapped(G_OBJECT(window), "destroy",
	G_CALLBACK(gtk_main_quit), NULL);

	// callback function for the menu
	g_signal_connect(G_OBJECT(quit), "activate",
	G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}
