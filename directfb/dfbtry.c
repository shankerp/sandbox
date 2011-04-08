#include <stdio.h>
#include <unistd.h>
#include <directfb.h>

/* This is the super interface, it's the entry point to all functionality. */
static IDirectFB *dfb = NULL;

/* The primary surface, i.e. the "screen".
 * In cooperative level DFSCL_FULLSCREEN it's the surface of the primary layer.
 */
static IDirectFBSurface *primary = NULL;

/* Store the width and height of the primary surface here to support all resolutions. */
static int screen_width  = 1920;
static int screen_height = 1080;

/* An error checking macro for a call to DirectFB.
 * It is suitable for very simple apllications or tutorials.
 * In more sophisticated applications this general error checking should not be used.
 */
#define DFBCHECK(x...)                                         \
  {                                                            \
    DFBResult err = x;                                         \
                                                               \
    if (err != DFB_OK)                                         \
      {                                                        \
        fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
        DirectFBErrorFatal( #x, err );                         \
      }                                                        \
  }

int main (int argc, char **argv)
{
    /* A surface description is needed to create a surface. */
    DFBSurfaceDescription dsc;

    /* Initialize DirectFB passing argc and argv
     * to support the standard DirectFB command line options.
     * DirectFB command line options will be stripped out automatically.
     */
    DFBCHECK (DirectFBInit (&argc, &argv));

    /* Create the super interface. */
    DFBCHECK (DirectFBCreate (&dfb));

    /* We want to go fullscreen,
     * the primary surface will be exclusive access to the surface of the primary layer.
     * If you disable this call a window will be created implicitly,
     * no further changes needed, flipping the surface updates the window.
     */
//    DFBCHECK (dfb->SetCooperativeLevel (dfb, DFSCL_FULLSCREEN));

    /* 1. Specify which fields of the struct are set.
     * 2. Fill out fields,
     * in this example we want to have a flippable primary surface.
     */
    dsc.flags = DSDESC_CAPS;
    dsc.caps  = DSCAPS_PRIMARY | DSCAPS_FLIPPING;

    /* Create the primary surface by passing our surface description. */
    DFBCHECK (dfb->CreateSurface( dfb, &dsc, &primary ));

    DFBCHECK (primary->GetSize (primary, &screen_width, &screen_height));
    DFBCHECK (primary->FillRectangle (primary, 0, 0, screen_width, screen_height));
    DFBCHECK (primary->SetColor (primary, 0x80, 0x80, 0xff, 0xff));
    DFBCHECK (primary->DrawLine (primary,
                0, screen_height / 2,
                screen_width - 1, screen_height / 2));
    DFBCHECK (primary->Flip (primary, NULL, 0));
    sleep (5);
    primary->Release( primary );
    dfb->Release( dfb );
    return 23;
}
