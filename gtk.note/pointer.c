#include <stdlib.h>

#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <cairo.h>

/* Signal handler invoked when user clicks on the button */
static void hello( GtkWidget *widget,
		gpointer data )
{
	GdkDisplay * display = gdk_display_get_default();
	g_printf( "hello, %s\n", gdk_display_get_name(display) );

	g_printf( "\t%d screens\n", gdk_display_get_n_screens(display) );

	GdkScreen * screen = gdk_display_get_default_screen( display);

	gint x,y;
//	gdk_display_get_pointer( display, NULL, &x, &y, NULL );
	GdkDeviceManager * device_manager = gdk_display_get_device_manager(
			display);
	GdkDevice *pointer = gdk_device_manager_get_client_pointer( device_manager );

	gdk_device_get_position( pointer,NULL, &x, &y );
	g_printf( "\tThe pointer coordinate is: (%d, %d)\n", x, y ); 

	gtk_window_move( (GtkWindow *)data, x, y );

}

void on_size_allocation( GtkWidget *widget, GdkRectangle *allocation,
		gpointer user_data)
{
	int width, height;
	cairo_surface_t * surface;
	cairo_t * cairo;
	cairo_region_t *shape;

	width = allocation -> width;
	height = allocation -> height;

	surface = cairo_image_surface_create( CAIRO_FORMAT_A1,
			width, height);
	cairo = cairo_create( surface );

	cairo_save( cairo ); 
	cairo_set_source_rgb( cairo, 0.0, 0.0, 0.0 );
	cairo_set_operator(cairo, CAIRO_OPERATOR_CLEAR );
	cairo_paint(cairo);

	cairo_set_source_rgb( cairo, 1.0, 1.0, 1.0 );
	cairo_set_operator( cairo,CAIRO_OPERATOR_SOURCE );
	cairo_arc( cairo, width/2.0, height/2.0, height/2.0, 0, 2*3.14 );
	cairo_fill( cairo );
	cairo_destroy( cairo );

	shape = gdk_cairo_region_create_from_surface( surface );

	gtk_widget_shape_combine_region( widget,shape );
	cairo_region_destroy( shape );
	
}

static gboolean draw(GtkWidget *widget, cairo_t *cr, gpointer userdata)
{

cairo_t *new_cr = gdk_cairo_create(gtk_widget_get_window(widget));

cairo_save( new_cr); 
cairo_set_source_rgba (new_cr, 0.9, 1.0, 0.90, 0.0); /*  transparent */
		   
/*  draw the background */
cairo_set_operator (new_cr, CAIRO_OPERATOR_SOURCE);
cairo_paint (new_cr);
cairo_destroy(new_cr);

return FALSE;
}

int main( int   argc,
          char *argv[] )
{
	GtkWidget *window;
	GtkWidget *close;
	GtkWidget *box;

	GtkWidget *grid; 
	GtkWidget *overlay;

	gtk_init (&argc, &argv);

	/* Create the toplevel window */

	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_default_size( (GtkWindow * )window, 200, 200);
	gtk_window_set_opacity( (GtkWindow *) window, 1 );

	gtk_widget_set_app_paintable(window, TRUE);
	g_signal_connect(G_OBJECT(window), "draw", G_CALLBACK(draw), NULL);

	//gtk_window_set_decorated( (GtkWindow * )window, FALSE);
	//gtk_window_set_resizable( (GtkWindow * )window, TRUE);

	box = gtk_event_box_new();
	//gtk_widget_set_app_paintable(box, TRUE);
	//g_signal_connect(G_OBJECT(box), "draw", G_CALLBACK(draw), NULL);
	g_signal_connect (window, "destroy",
		    G_CALLBACK (exit), NULL);


	close = gtk_button_new_with_label ("X");
	gtk_widget_set_size_request(close , 25, 25);
	gtk_widget_set_halign(close, GTK_ALIGN_END );
	gtk_widget_set_valign(close, GTK_ALIGN_START );
	gtk_widget_set_hexpand(close, TRUE);

	//grid = gtk_grid_new();

	overlay = gtk_overlay_new();
	gtk_container_add( GTK_CONTAINER(overlay ), box);
//	gtk_container_add( GTK_CONTAINER(grid), close);
	gtk_overlay_add_overlay( (GtkOverlay *) overlay, close );

	gtk_container_add (GTK_CONTAINER (window), overlay);
	g_signal_connect ( close , "clicked",
		    G_CALLBACK (hello), (gpointer) window);


	g_signal_connect ( box, "size-allocate",
		    G_CALLBACK (on_size_allocation), NULL);

GdkScreen *screen = gtk_widget_get_screen( (GtkWidget *) window);
GdkVisual *visual = gdk_screen_get_rgba_visual(screen);
if (!visual)
	g_printf("ohoho");
gtk_widget_set_visual((GtkWidget*) window, visual);

	gtk_widget_show_all(window);

	gtk_main ();

	return 0;
}


