#include <gtk/gtk.h>

int main( int   argc,
          char *argv[] )
{
  /* GtkWidget is the storage type for widgets */
  GtkWidget *window;
  GtkWidget *frame;

  /* Initialise GTK */
  gtk_init (&argc, &argv);
    
  /* Create a new window */
  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Frame Example");

  /* Here we connect the "destroy" event to a signal handler */ 
  g_signal_connect (window, "destroy",
		    G_CALLBACK (gtk_main_quit), NULL);

  gtk_widget_set_size_request (window, 300, 300);
  /* Sets the border width of the window. */
  gtk_container_set_border_width (GTK_CONTAINER (window), 10);

  /* Create a Frame */
  frame = gtk_frame_new (NULL);
  gtk_container_add (GTK_CONTAINER (window), frame);

  /* Set the frame's label */
  gtk_frame_set_label (GTK_FRAME (frame), "百度百科");

  /* Align the label at the right of the frame */
  gtk_frame_set_label_align (GTK_FRAME (frame), 0.0, 1.0);

  /* Set the style of the frame */
  gtk_frame_set_shadow_type (GTK_FRAME (frame), GTK_SHADOW_ETCHED_OUT);

  GtkWidget * header = gtk_label_new(NULL);
  const gchar *text = "Go to the <a href=\"http://www.gtk.org\">GTK+ website</a> for more...";
  gtk_label_set_markup ((GtkLabel *)header, text);
  gtk_frame_set_label_widget (GTK_FRAME (frame), header);
  //gtk_container_add(GTK_CONTAINER(frame),header ); 

  
  /* Display the window */
  gtk_widget_show_all (window);
    
  /* Enter the event loop */
  gtk_main ();
    
  return 0;
}
