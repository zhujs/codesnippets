
#include <stdlib.h>

#include <gtk/gtk.h>
#include <gdk/gdk.h>


// callback function called when clipboard contents are changed 
void onClipboardChange( GtkClipboard *clipboard, GdkEvent *event,
		gpointer user_data)
{
	g_printf( "%d\n", event->type );
	// requests the contents of the primary clipboard
	gchar* text = gtk_clipboard_wait_for_text( clipboard );
	if (text != NULL )
	{
		g_printf( "%s\n", text);
		g_free( text );
	}
}

int main( int   argc,
          char *argv[] )
{

	gtk_init(&argc, &argv);

	GtkWidget * win = gtk_window_new( GTK_WINDOW_TOPLEVEL );
	// get the default display
	GdkDisplay * display = gdk_display_get_default();
	// get the default clipboard for the display
	GtkClipboard * primary = gtk_clipboard_get_for_display( display,
			GDK_SELECTION_PRIMARY );


	// resgister the owner-change signal for clipboard
	g_signal_connect(G_OBJECT(primary), "owner-change",
		G_CALLBACK( onClipboardChange ), NULL);

	gtk_main();
	return 0;
}


