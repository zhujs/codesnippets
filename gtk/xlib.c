#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>

/* The window which contains the text. */

struct {
    int width;
    int height;

    /* The strings containing the information. */

    char * coord_text;
    int coord_text_len;
    char * size_text;
    int size_text_len;

    /* X Windows related variables. */

    Display * display;
    int screen;
    Window root;
    Window window;
    GC gc;
    XFontStruct * font;
    unsigned long black_pixel;    
    unsigned long white_pixel;
}
text_box;

/* Connect to the display, set up the basic variables. */

static void x_connect ()
{
    text_box.display = XOpenDisplay (NULL);
    if (! text_box.display) {
        fprintf (stderr, "Could not open display.\n");
        exit (1);
    }
    text_box.screen = DefaultScreen (text_box.display);
    text_box.root = RootWindow (text_box.display, text_box.screen);
    text_box.black_pixel = BlackPixel (text_box.display, text_box.screen);
    text_box.white_pixel = WhitePixel (text_box.display, text_box.screen);
}

/* Create the window. */

static void create_window ()
{
    text_box.width = 300;
    text_box.height = 300;
    text_box.window = 
        XCreateSimpleWindow (text_box.display,
                             text_box.root,
                             1, /* x */
                             1, /* y */
                             text_box.width,
                             text_box.height,
                             0, /* border width */
                             text_box.black_pixel, /* border pixel */
                             text_box.white_pixel  /* background */);
    XSelectInput (text_box.display, text_box.window,
                  ExposureMask |

                  /* Add StructureNotifyMask to send us events
                     involving resizing of the window, etc. */

                  StructureNotifyMask);
    XMapWindow (text_box.display, text_box.window);
}

/* Set up the GC (Graphics Context). */

static void set_up_gc ()
{
    text_box.screen = DefaultScreen (text_box.display);
    text_box.gc = XCreateGC (text_box.display, text_box.window, 0, 0);
    XSetBackground (text_box.display, text_box.gc, text_box.white_pixel); 
    XSetForeground (text_box.display, text_box.gc, text_box.black_pixel); 
}

/* Set up the text font. */

static void set_up_font ()
{
    const char * fontname = "-*-helvetica-*-r-*-*-18-*-*-*-*-*-*-*";
    text_box.font = XLoadQueryFont (text_box.display, fontname);
    /* If the font could not be loaded, revert to the "fixed" font. */
    if (! text_box.font) {
        fprintf (stderr, "unable to load font %s: using fixed\n", fontname);
        text_box.font = XLoadQueryFont (text_box.display, "fixed");
    }
    XSetFont (text_box.display, text_box.gc, text_box.font->fid);
}

/* Get the current coordinates of the window. */

static void get_coordinates ()
{
    int x, y;
    Window child_return;

    XTranslateCoordinates (text_box.display, text_box.window, text_box.root,
                           0, 0, & x, & y, & child_return);
    if (text_box.coord_text) {
        free (text_box.coord_text);
    }
    if (text_box.size_text) {
        free (text_box.size_text);
    }
    text_box.coord_text_len =
        asprintf (& text_box.coord_text, "Coordinates are x:%d y:%d", x, y);
    text_box.size_text_len =
        asprintf (& text_box.size_text, "Sizes are width:%d height:%d",
                  text_box.width, text_box.height);
}

/* Put "text" at coordinates "x" and "y". */

static void put_text (int x, int y, const char * text, int text_len)
{
    XDrawString (text_box.display, text_box.window, text_box.gc,
                 x, y, text, text_len);
}

/* Draw the window. */

static void draw_screen ()
{
    int x;
    int y;
    int direction;
    int ascent;
    int descent;
    XCharStruct overall;

    get_coordinates ();

    XClearWindow (text_box.display, text_box.window);

    /* Text placement. */

    XTextExtents (text_box.font, text_box.coord_text, text_box.coord_text_len,
                  & direction, & ascent, & descent, & overall);
    x = (text_box.width - overall.width) / 2;
    y = text_box.height / 4 + ascent/2;
    put_text (x, y, text_box.coord_text, text_box.coord_text_len);
    XTextExtents (text_box.font, text_box.size_text, text_box.size_text_len,
                  & direction, & ascent, & descent, & overall);
    x = (text_box.width - overall.width) / 2;
    y = (3 * text_box.height) / 4 + ascent/2;
    put_text (x, y, text_box.size_text, text_box.size_text_len);
}

/* Loop over events. */

static void event_loop ()
{
    Atom wm_delete_window;
    wm_delete_window =
        XInternAtom (text_box.display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols (text_box.display, text_box.window, &wm_delete_window, 1);

    while (1) {
        XEvent e;
        XNextEvent (text_box.display, & e);
        if (e.type == Expose) {
            draw_screen ();
        }
        else if (e.type == ConfigureNotify) {
            XConfigureEvent xce = e.xconfigure;
            if (xce.width != text_box.width ||
                xce.height != text_box.height) {
                text_box.width = xce.width;
                text_box.height = xce.height;
            }
            draw_screen ();
        }
        else if (e.type == ClientMessage) {
            if ((Atom)e.xclient.data.l[0] == wm_delete_window) {
                break;
            }
        }
    }
}


int main (int argc, char ** argv)
{
    text_box.coord_text = 0;
    text_box.coord_text_len = 0;
    x_connect ();
    create_window ();
    set_up_gc ();
    set_up_font ();
    event_loop ();
    return 0;
}

