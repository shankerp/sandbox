/* Toy widget for GTK+ for displaying MNG animations.
 *
 * Copyright (C) 2000 The Free Software Foundation
 *
 * Author(s): Volodymyr Babin <vb@dwuj.ichf.edu.pl>
 *
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#define MNG_APP_CMS
#define MNG_ACCESS_CHUNKS
#define MNG_STORE_CHUNKS


#include <gtk/gtkmain.h>
#include "iterate_mng.h"
#include <gdk-pixbuf/gdk-pixbuf.h>

/* MNG callbacks */

G_DEFINE_TYPE(GtkMngView, gtk_mng_view, GTK_TYPE_WIDGET);
#define BS_CHANGES
#if 0
#define FUNCTION_ENTRY() printf("ENTRY %d %s %s\n", __LINE__, __FUNCTION__, __FILE__)
#define FUNCTION_EXIT() printf("EXIT %d %s %s\n", __LINE__, __FUNCTION__, __FILE__)
#else
#define FUNCTION_ENTRY()
#define FUNCTION_EXIT()
#endif

void dump_chunk_type(mng_chunkid iChunktype)
{
    switch(iChunktype)
    {
        case MNG_UINT_HUH :
            printf("Type is MNG_UINT_HUH \n");
            break;
        case MNG_UINT_BACK:
            printf("Type is MNG_UINT_BACK\n");
            break;
        case MNG_UINT_BASI:
            printf("Type is MNG_UINT_BASI\n");
            break;
        case MNG_UINT_CLIP:
            printf("Type is MNG_UINT_CLIP\n");
            break;
        case MNG_UINT_CLON:
            printf("Type is MNG_UINT_CLON\n");
            break;
        case MNG_UINT_DBYK:
            printf("Type is MNG_UINT_DBYK\n");
            break;
        case MNG_UINT_DEFI:
            printf("Type is MNG_UINT_DEFI\n");
            break;
        case MNG_UINT_DHDR:
            printf("Type is MNG_UINT_DHDR\n");
            break;
        case MNG_UINT_DISC:
            printf("Type is MNG_UINT_DISC\n");
            break;
        case MNG_UINT_DROP:
            printf("Type is MNG_UINT_DROP\n");
            break;
        case MNG_UINT_ENDL:
            printf("Type is MNG_UINT_ENDL\n");
            break;
        case MNG_UINT_FRAM:
            printf("Type is MNG_UINT_FRAM\n");
            break;
        case MNG_UINT_IDAT:
            printf("Type is MNG_UINT_IDAT\n");
            break;
        case MNG_UINT_IEND:
            printf("Type is MNG_UINT_IEND\n");
            break;
        case MNG_UINT_IHDR:
            printf("Type is MNG_UINT_IHDR\n");
            break;
        case MNG_UINT_IJNG:
            printf("Type is MNG_UINT_IJNG\n");
            break;
        case MNG_UINT_IPNG:
            printf("Type is MNG_UINT_IPNG\n");
            break;
        case MNG_UINT_JDAA:
            printf("Type is MNG_UINT_JDAA\n");
            break;
        case MNG_UINT_JDAT:
            printf("Type is MNG_UINT_JDAT\n");
            break;
        case MNG_UINT_JHDR:
            printf("Type is MNG_UINT_JHDR\n");
            break;
        case MNG_UINT_JSEP:
            printf("Type is MNG_UINT_JSEP\n");
            break;
        case MNG_UINT_JdAA:
            printf("Type is MNG_UINT_JdAA\n");
            break;
        case MNG_UINT_LOOP:
            printf("Type is MNG_UINT_LOOP\n");
            break;
        case MNG_UINT_MAGN:
            printf("Type is MNG_UINT_MAGN\n");
            break;
        case MNG_UINT_MEND:
            printf("Type is MNG_UINT_MEND\n");
            break;
        case MNG_UINT_MHDR:
            printf("Type is MNG_UINT_MHDR\n");
            break;
        case MNG_UINT_MOVE:
            printf("Type is MNG_UINT_MOVE\n");
            break;
        case MNG_UINT_ORDR:
            printf("Type is MNG_UINT_ORDR\n");
            break;
        case MNG_UINT_PAST:
            printf("Type is MNG_UINT_PAST\n");
            break;
        case MNG_UINT_PLTE:
            printf("Type is MNG_UINT_PLTE\n");
            break;
        case MNG_UINT_PPLT:
            printf("Type is MNG_UINT_PPLT\n");
            break;
        case MNG_UINT_PROM:
            printf("Type is MNG_UINT_PROM\n");
            break;
        case MNG_UINT_SAVE:
            printf("Type is MNG_UINT_SAVE\n");
            break;
        case MNG_UINT_SEEK:
            printf("Type is MNG_UINT_SEEK\n");
            break;
        case MNG_UINT_SHOW:
            printf("Type is MNG_UINT_SHOW\n");
            break;
        case MNG_UINT_TERM:
            printf("Type is MNG_UINT_TERM\n");
            break;
        case MNG_UINT_adAT:
            printf("Type is MNG_UINT_adAT\n");
            break;
        case MNG_UINT_ahDR:
            printf("Type is MNG_UINT_ahDR\n");
            break;
        case MNG_UINT_bKGD:
            printf("Type is MNG_UINT_bKGD\n");
            break;
        case MNG_UINT_cHRM:
            printf("Type is MNG_UINT_cHRM\n");
            break;
        case MNG_UINT_eXPI:
            printf("Type is MNG_UINT_eXPI\n");
            break;
        case MNG_UINT_evNT:
            printf("Type is MNG_UINT_evNT\n");
            break;
        case MNG_UINT_fPRI:
            printf("Type is MNG_UINT_fPRI\n");
            break;
        case MNG_UINT_gAMA:
            printf("Type is MNG_UINT_gAMA\n");
            break;
        case MNG_UINT_hIST:
            printf("Type is MNG_UINT_hIST\n");
            break;
        case MNG_UINT_iCCP:
            printf("Type is MNG_UINT_iCCP\n");
            break;
        case MNG_UINT_iTXt:
            printf("Type is MNG_UINT_iTXt\n");
            break;
        case MNG_UINT_mpNG:
            printf("Type is MNG_UINT_mpNG\n");
            break;
        case MNG_UINT_nEED:
            printf("Type is MNG_UINT_nEED\n");
            break;
        case MNG_UINT_oFFs:
            printf("Type is MNG_UINT_oFFs\n");
            break;
        case MNG_UINT_pCAL:
            printf("Type is MNG_UINT_pCAL\n");
            break;
        case MNG_UINT_pHYg:
            printf("Type is MNG_UINT_pHYg\n");
            break;
        case MNG_UINT_pHYs:
            printf("Type is MNG_UINT_pHYs\n");
            break;
        case MNG_UINT_sBIT:
            printf("Type is MNG_UINT_sBIT\n");
            break;
        case MNG_UINT_sCAL:
            printf("Type is MNG_UINT_sCAL\n");
            break;
        case MNG_UINT_sPLT:
            printf("Type is MNG_UINT_sPLT\n");
            break;
        case MNG_UINT_sRGB:
            printf("Type is MNG_UINT_sRGB\n");
            break;
        case MNG_UINT_tEXt:
            printf("Type is MNG_UINT_tEXt\n");
            break;
        case MNG_UINT_tIME:
            printf("Type is MNG_UINT_tIME\n");
            break;
        case MNG_UINT_tRNS:
            printf("Type is MNG_UINT_tRNS\n");
            break;
        case MNG_UINT_zTXt:
            printf("Type is MNG_UINT_zTXt\n");
            break;
        default:
            printf("WHOA!! DEFAULT! %d\n", iChunktype);
            sleep(3);
            break;
    }
}

    static mng_ptr
mng_malloc_callback (mng_size_t how_many)
{
    FUNCTION_ENTRY();
    FUNCTION_EXIT();
    return (mng_ptr) g_new0 (gchar, how_many);
}

    static void
mng_free_callback (mng_ptr pointer, mng_size_t number)
{
    FUNCTION_ENTRY();
    g_free (pointer);
}

    static mng_bool
mng_open_stream_callback (mng_handle mng_h)
{
    FUNCTION_ENTRY();
    FUNCTION_EXIT();
    return MNG_TRUE;
}

    static mng_bool
mng_close_stream_callback (mng_handle mng_h)
{
    FUNCTION_ENTRY();
    FUNCTION_EXIT();
    return MNG_TRUE;
}

    static mng_bool
mng_read_data_callback (mng_handle mng_h,
        mng_ptr buffer,
        mng_uint32 bytes_requested,
        mng_uint32 * bytes_read)
{
    FUNCTION_ENTRY();
    *bytes_read = 0;
    return MNG_FALSE;
}

int g_width = 0;
int g_height = 0;
    static mng_bool
mng_process_header_callback (mng_handle mng_h,
        mng_uint32 width,
        mng_uint32 height)
{
    FUNCTION_ENTRY();
    GtkMngView * mng_view;

    mng_view = GTK_MNG_VIEW (mng_get_userdata (mng_h));

    mng_view->width = width;
    mng_view->height = height;
    g_width = width;
    g_height = height;

    g_free (mng_view->MNG_drawing_buffer);
    mng_view->MNG_drawing_buffer = g_new0 (guchar, 3 * width * height);

    g_free (mng_view->MNG_alpha_buffer);
    mng_view->MNG_alpha_buffer = g_new0 (guchar, width * height);

    printf("width %d height %d\n", width, height);
    printf("mng_get_framecount       %d\n", mng_get_framecount(mng_view->MNG_handle));
    printf("mng_get_layercount       %d\n", mng_get_layercount(mng_view->MNG_handle));
    printf("mng_get_playtime       %d\n", mng_get_playtime(mng_view->MNG_handle));
    printf("mng_get_ticks       %d\n", mng_get_ticks(mng_view->MNG_handle));
    printf("mng_get_colortype       %d\n", mng_get_colortype(mng_view->MNG_handle));
    printf("mng_get_interlace       %d\n", mng_get_interlace(mng_view->MNG_handle));
    printf("mng_get_viewgamma       %f\n", mng_get_viewgamma(mng_view->MNG_handle));
    printf("mng_get_displaygamma    %f\n", mng_get_displaygamma(mng_view->MNG_handle));
    printf("mng_get_dfltimggamma    %f\n", mng_get_dfltimggamma(mng_view->MNG_handle));
    printf("mng_get_viewgammaint    %d\n", mng_get_viewgammaint(mng_view->MNG_handle));
    printf("mng_get_displaygammaint %d\n", mng_get_displaygammaint(mng_view->MNG_handle));
    printf("mng_get_dfltimggammaint %d\n", mng_get_dfltimggammaint(mng_view->MNG_handle));

    gtk_widget_queue_resize (GTK_WIDGET (mng_view));
    FUNCTION_EXIT();
    return MNG_TRUE;
}

    static mng_bool
mng_process_mend_callback (mng_handle mng_h,
        mng_uint32  iIterationsdone,
        mng_uint32  iIterationsleft)
{
    printf("MEND MEND MEND MEND\n");
    printf("iIterationsdone %d\n", iIterationsdone);
    printf("iIterationsleft %d\n", iIterationsleft);
    printf("mng_get_framecount       %d\n", mng_get_framecount(mng_h));
    printf("mng_get_layercount       %d\n", mng_get_layercount(mng_h));
    printf("mng_get_playtime       %d\n", mng_get_playtime(mng_h));
    printf("mng_get_ticks       %d\n", mng_get_ticks(mng_h));
    printf("mng_get_totalframes     %d\n", mng_get_totalframes     (mng_h));
    printf("mng_get_totallayers     %d\n", mng_get_totallayers     (mng_h));
    printf("mng_get_totalplaytime   %d\n", mng_get_totalplaytime   (mng_h));
}

    static mng_bool
mng_process_term_callback (mng_handle mng_h,
        mng_uint8   iTermaction,
        mng_uint8   iIteraction,
        mng_uint32  iDelay,
        mng_uint32  iItermax)
{
    switch(iTermaction)
    {
        case MNG_TERMACTION_LASTFRAME :
            printf("MNG_TERMACTION_LASTFRAME \n");
            break;
        case MNG_TERMACTION_CLEAR     :
            printf("MNG_TERMACTION_CLEAR     \n");
            break;
        case MNG_TERMACTION_FIRSTFRAME:
            printf("MNG_TERMACTION_FIRSTFRAME\n");
            break;
        case MNG_TERMACTION_REPEAT    :
            printf("MNG_TERMACTION_REPEAT    \n");
            break;


    }
    printf("iiTeraction %d\n", iIteraction);
    printf("Delay %d\n", iDelay);
    printf("iItermax %d\n", iItermax);
}

static void gtk_mng_view_paint (GtkMngView *, GdkRectangle *);

    static gboolean
gtk_mng_view_init_libmng (GtkMngView * mng_view)
{
    FUNCTION_ENTRY();
    GtkWidget * widget;

    g_return_val_if_fail (IS_GTK_MNG_VIEW (mng_view), FALSE);

    if (mng_view->MNG_handle)
        mng_cleanup (&mng_view->MNG_handle);

    mng_view->MNG_handle = mng_initialize (mng_view,
            mng_malloc_callback,
            mng_free_callback,
            MNG_NULL);

    if (mng_view->MNG_handle == MNG_NULL) {
        FUNCTION_EXIT();
        return FALSE;
    }

    if (mng_setcb_openstream (mng_view->MNG_handle, mng_open_stream_callback) != MNG_NOERROR ||
            mng_setcb_closestream (mng_view->MNG_handle, mng_close_stream_callback) != MNG_NOERROR ||
            mng_setcb_readdata (mng_view->MNG_handle, mng_read_data_callback) != MNG_NOERROR ||
            mng_setcb_processheader (mng_view->MNG_handle, mng_process_header_callback) != MNG_NOERROR ||
            mng_setcb_processmend (mng_view->MNG_handle, mng_process_mend_callback) != MNG_NOERROR ||
            mng_setcb_processterm (mng_view->MNG_handle, mng_process_term_callback) != MNG_NOERROR)
    {
        mng_cleanup (&mng_view->MNG_handle);
        FUNCTION_EXIT();
        return FALSE;
    }

    mng_set_canvasstyle (mng_view->MNG_handle, MNG_CANVAS_RGB8_A8);

    widget = GTK_WIDGET (mng_view);

    if (!GTK_WIDGET_REALIZED (widget))
        gtk_widget_realize (widget);

    FUNCTION_EXIT();
    return TRUE;
}

/* GTK+ widget methods */

    static void
gtk_mng_view_finalize (GObject * obj)
{
    FUNCTION_ENTRY();
    GtkMngView * mng_view;

    g_return_if_fail (IS_GTK_MNG_VIEW (obj));

    mng_view = (GtkMngView *) obj;

    if (mng_view->timeout_ID)
        g_source_remove (mng_view->timeout_ID);

    g_free (mng_view->MNG_drawing_buffer);
    g_free (mng_view->MNG_alpha_buffer);

    if (mng_view->MNG_handle)
        mng_cleanup (&mng_view->MNG_handle);

    G_OBJECT_CLASS(gtk_mng_view_parent_class)->finalize(obj);
}

    static void
gtk_mng_view_size_request (GtkWidget * widget, GtkRequisition * requisition)
{
    FUNCTION_ENTRY();
    GtkMngView * mng_view;

    g_return_if_fail (IS_GTK_MNG_VIEW (widget));
    g_return_if_fail (requisition != NULL);

    mng_view = (GtkMngView *) widget;

    requisition->width = mng_view->width;
    requisition->height = mng_view->height;
}

    static void
gtk_mng_view_size_allocate (GtkWidget * widget, GtkAllocation * allocation)
{
    FUNCTION_ENTRY();
    g_return_if_fail (IS_GTK_MNG_VIEW (widget));
    g_return_if_fail (allocation != NULL);

    if (GTK_WIDGET_REALIZED (widget))
        gdk_window_move_resize (widget->window,
                allocation->x,
                allocation->y,
                allocation->width,
                allocation->height);
}

    static void
gtk_mng_view_paint (GtkMngView * mng_view,
        GdkRectangle * area)
{
    FUNCTION_ENTRY();
    GtkWidget * widget;
    guint rowstride;
    guchar * buffer;
    register guchar * ptr;
    register guchar * bptr;
    register guchar * aptr;

    widget = GTK_WIDGET (mng_view);

    g_assert (GTK_WIDGET_REALIZED (widget));

#ifdef BS_CHANGES
    int i = 0, j = 0, k = 0;
    rowstride = 4 * area->width;
#else
    rowstride = 3 * area->width;
#endif
    buffer = g_new (guchar, rowstride * area->height);


    bptr = buffer;
    ptr = mng_view->MNG_drawing_buffer
        + 3 * (area->y * mng_view->width + area->x); 
    aptr = mng_view->MNG_alpha_buffer
        + (area->y * mng_view->width + area->x); 

#ifdef BS_CHANGES
    while (bptr < buffer + rowstride * area->height)
    {
        // Copying BGR to RGBA
        for (i = 0, j = 0, k = 0; i < rowstride ; i+=4, j+=3, k++) {
            bptr[i] = ptr[j + 2]; // R
            bptr[i+1] = ptr[j + 1]; // G
            bptr[i+2] = ptr[j]; // B
            bptr[i+3] = aptr[k]; // Alpha value
        }
        bptr += rowstride;
        ptr += 3 * mng_view->width;
        aptr += mng_view->width;
    }
#else
    while (bptr < buffer + rowstride * area->height)
    {
        memcpy (bptr, ptr, rowstride);
        bptr += rowstride;
        ptr += 3 * mng_view->width;
    }
#endif

#ifdef BS_CHANGES
    printf("PAINTING USING CAIRO\n");
    printf("PAINTING USING CAIRO\n");
    printf("PAINTING USING CAIRO\n");
    printf("PAINTING USING CAIRO\n");
    cairo_surface_t *surface = cairo_image_surface_create_for_data(mng_view->MNG_drawing_buffer, CAIRO_FORMAT_ARGB32, area->width, area->height, rowstride);
    cairo_t *cr = gdk_cairo_create(widget->window);
    cairo_set_source_surface(cr, surface, area->x, area->y);
    cairo_paint(cr);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
#else
    gdk_draw_rgb_image (widget->window,
            widget->style->white_gc,
            area->x,
            area->y,
            area->width,
            area->height,
            GDK_RGB_DITHER_NORMAL,
            buffer,
            rowstride);
#endif

    g_free (buffer);
    gdk_flush ();
}

    static gboolean
gtk_mng_view_expose (GtkWidget * widget, GdkEventExpose * event)
{
    FUNCTION_ENTRY();
    g_return_val_if_fail (IS_GTK_MNG_VIEW (widget), FALSE);
    g_return_val_if_fail (event != NULL, FALSE);

    if (GTK_WIDGET_REALIZED (widget))
    {
        GdkRectangle dummy;
        GdkRectangle rectangle;
        GtkMngView * mng_view;

        mng_view = GTK_MNG_VIEW (widget);
        dummy.x = dummy.y = 0;
        dummy.width = mng_view->width;
        dummy.height = mng_view->height;

        if (gdk_rectangle_intersect (&dummy, &event->area, &rectangle))
            gtk_mng_view_paint (mng_view, &rectangle);
        //mng_display_resume(mng_view->MNG_handle);
    }
    FUNCTION_EXIT();
    return FALSE;
}

    static void
gtk_mng_view_realize (GtkWidget * widget)
{
    FUNCTION_ENTRY();
    GdkWindowAttr attributes;
    gint attributes_mask;

    g_return_if_fail (IS_GTK_MNG_VIEW (widget));

    GTK_WIDGET_SET_FLAGS (widget, GTK_REALIZED);

    attributes.window_type = GDK_WINDOW_CHILD;
    attributes.x = widget->allocation.x;
    attributes.y = widget->allocation.y;
    attributes.width = widget->allocation.width;
    attributes.height = widget->allocation.height;
    attributes.wclass = GDK_INPUT_OUTPUT;
    attributes.visual = gtk_widget_get_visual (widget);
    attributes.colormap = gtk_widget_get_colormap (widget);
    attributes.event_mask = gtk_widget_get_events (widget);
    attributes.event_mask |= GDK_EXPOSURE_MASK;
    attributes_mask = GDK_WA_X | GDK_WA_Y | GDK_WA_VISUAL | GDK_WA_COLORMAP;
    widget->window = gdk_window_new (gtk_widget_get_parent_window (widget),
            &attributes, attributes_mask);
    gdk_window_set_user_data (widget->window, widget);
    widget->style = gtk_style_attach (widget->style, widget->window);
    gtk_style_set_background (widget->style, widget->window, GTK_STATE_NORMAL);
}

    static void
gtk_mng_view_init (GtkMngView * mng_view)
{
    FUNCTION_ENTRY();
    g_return_if_fail (IS_GTK_MNG_VIEW (mng_view));

    GTK_WIDGET_UNSET_FLAGS (GTK_WIDGET (mng_view), GTK_NO_WINDOW);

    mng_view->MNG_handle = NULL;
    mng_view->MNG_drawing_buffer = NULL;
    mng_view->MNG_alpha_buffer = NULL;
    mng_view->timeout_ID = 0;
    mng_view->mng_food = NULL;
}

    static void
gtk_mng_view_class_init (GtkMngViewClass * klass)
{
    FUNCTION_ENTRY();
    GObjectClass * object_class;
    GtkWidgetClass * widget_class;

    g_return_if_fail (IS_GTK_MNG_VIEW_CLASS (klass));

    object_class = (GObjectClass *) klass;
    object_class->finalize = gtk_mng_view_finalize;

    widget_class = (GtkWidgetClass *) klass;
    widget_class->size_request = gtk_mng_view_size_request;
    widget_class->size_allocate = gtk_mng_view_size_allocate;
    widget_class->expose_event = gtk_mng_view_expose;
    widget_class->realize = gtk_mng_view_realize;
}

    GtkMngView *
gtk_mng_view_new (void)
{
    FUNCTION_ENTRY();
    FUNCTION_EXIT();
    return GTK_MNG_VIEW (g_object_new(GTK_MNG_VIEW_TYPE, NULL));
}

    gboolean
gtk_mng_view_load_mng_from_memory (GtkMngView * mng_view,
        guchar * data_to_eat,
        guint data_size)
{
    FUNCTION_ENTRY();
    guint available_mng_food;
    g_return_val_if_fail (IS_GTK_MNG_VIEW (mng_view), FALSE);
    g_return_val_if_fail (data_size > 27, FALSE);
    g_return_val_if_fail (data_to_eat != NULL, FALSE);

    //if (data_to_eat[0] != 0x8a ||
    //    data_to_eat[1] != 'M' ||
    //    data_to_eat[2] != 'N' ||
    //    data_to_eat[3] != 'G' ||
    //    data_to_eat[4] != 0x0d ||
    //    data_to_eat[5] != 0x0a ||
    //    data_to_eat[6] != 0x1a ||
    //    data_to_eat[7] != 0x0a)
    //{
    //  g_warning ("not mng format");
    //  FUNCTION_EXIT();
    //  return FALSE;
    //}

    if (gtk_mng_view_init_libmng (mng_view))
    {
        mng_view->bytes_to_eat = data_size;
        mng_view->bytes_eaten = 0;
        mng_view->mng_food = data_to_eat;

        //if (mng_read (mng_view->MNG_handle) != MNG_NOERROR)
        {
            available_mng_food = mng_view->bytes_to_eat - mng_view->bytes_eaten;
            if (available_mng_food > 0 && mng_view->mng_food != NULL)
            {
                //* bytes_read = (mng_uint32) MIN ((mng_uint32) available_mng_food, bytes_requested);
                //memcpy (buffer, mng_view->mng_food + mng_view->bytes_eaten, * bytes_read);
                //printf("available_mng_food %d\n", available_mng_food);
                mng_read_pushdata (mng_view->MNG_handle, mng_view->mng_food, available_mng_food, MNG_FALSE); 
                //mng_read_resume(mng_view->MNG_handle);
                //mng_view->bytes_eaten += * bytes_read;
                FUNCTION_EXIT();
                return MNG_TRUE;
            }
            g_warning ("libmng read error");
            mng_cleanup (&mng_view->MNG_handle);
            FUNCTION_EXIT();
            return FALSE;
        }
        //  else {
        FUNCTION_EXIT();
        // }
    }
    else
    {
        g_warning ("error initializing libmng");
        FUNCTION_EXIT();
        return FALSE;
    }
    FUNCTION_EXIT();
    return TRUE;
}

static mng_bool myiterchunk (mng_handle  hMNG,
        mng_handle  hChunk,
        mng_chunkid iChunktype,
        mng_uint32  iChunkseq)
{
    static int databytes = 0;
    int length = 0;
    GtkMngView *mng_view = GTK_MNG_VIEW (mng_get_userdata (hMNG));

    printf("FRAME DELAY %d\n", mng_get_currframdelay(hMNG));
    int iWidth, iHeight, iTicks, iLayercount, iFramecount, iPlaytime, iSimplicity;
    mng_bool         bEmpty;
    mng_uint8        iMode;
    mng_uint32       iNamesize;
    mng_pchar        zName;
    mng_uint8        iChangedelay;
    mng_uint8        iChangetimeout;
    mng_uint8        iChangeclipping;
    mng_uint8        iChangesyncid;
    mng_uint32       iDelay;
    mng_uint32       iTimeout;
    mng_uint8        iBoundarytype;
    mng_int32        iBoundaryl;
    mng_int32        iBoundaryr;
    mng_int32        iBoundaryt;
    mng_int32        iBoundaryb;
    mng_uint32       iCount;
    mng_uint32p      pSyncids;

    dump_chunk_type(iChunktype);

    mng_getchunk_idat(hMNG, hChunk, &length, mng_view->MNG_drawing_buffer + databytes);
    databytes += length;
    if (databytes >= 3*g_width*g_height) {
        printf("DATABYTES %d WIDTH %d HEIGHT %d 3 TIMES %d\n", databytes, g_width, g_height, 3*g_width*g_height);
        databytes = 0;
    }
    int i = 0;
    //for ( i = 0; i < length; i++)
    //    printf("%x ", mng_view->MNG_drawing_buffer[i]);

    if(iChunktype == MNG_UINT_MHDR) {
        mng_getchunk_mhdr (hMNG,
                hChunk,
                &iWidth,
                &iHeight,
                &iTicks,
                &iLayercount,
                &iFramecount,
                &iPlaytime,
                &iSimplicity);
        //printf("iWidth,     %d\n", iWidth);
        //printf("iHeight,    %d\n", iHeight);
        //printf("iTicks,     %d\n", iTicks);
        //printf("iLayercount %d\n", iLayercount);
        //printf("iFramecount %d\n", iFramecount);
        //printf("iPlaytime,  %d\n", iPlaytime);
        //printf("iSimplicity %d\n", iSimplicity);
    }
    if(iChunktype == MNG_UINT_FRAM) {
        mng_getchunk_fram       (hMNG,
                hChunk,
                &bEmpty,
                &iMode,
                &iNamesize,
                &zName,
                &iChangedelay,
                &iChangetimeout,
                &iChangeclipping,
                &iChangesyncid,
                &iDelay,
                &iTimeout,
                &iBoundarytype,
                &iBoundaryl,
                &iBoundaryr,
                &iBoundaryt,
                &iBoundaryb,
                &iCount,
                &pSyncids);

        printf("Framing iMode %d\n", iMode);
        switch(iMode)
        {
            case MNG_FRAMINGMODE_NOCHANGE:
                printf("Mode No change\n");
                break;
            case MNG_FRAMINGMODE_1       :
                printf("Mode 1\n");
                break;
            case MNG_FRAMINGMODE_2       :
                printf("Mode 2\n");
                break;
            case MNG_FRAMINGMODE_3       :
                printf("Mode 3\n");
                break;
            case MNG_FRAMINGMODE_4       :
                printf("Mode 4\n");
                break;
        }
    }
    return MNG_TRUE;
}

    gboolean
gtk_mng_view_load_mng_from_memory_remaining (GtkMngView * mng_view,
        guchar * data_to_eat,
        guint data_size)
{
    mng_read_pushdata (mng_view->MNG_handle, data_to_eat, data_size, MNG_FALSE); 
    mng_read(mng_view->MNG_handle);
    mng_iterate_chunks (mng_view->MNG_handle, 0, myiterchunk);
    printf("mng_get_framecount       %d\n", mng_get_framecount(mng_view->MNG_handle));
    printf("mng_get_layercount       %d\n", mng_get_layercount(mng_view->MNG_handle));
    printf("mng_get_playtime       %d\n", mng_get_playtime(mng_view->MNG_handle));
    printf("mng_get_ticks       %d\n", mng_get_ticks(mng_view->MNG_handle));
    printf("mng_get_starttime       %d\n", mng_get_starttime       (mng_view->MNG_handle));
    printf("mng_get_runtime         %d\n", mng_get_runtime         (mng_view->MNG_handle));
    printf("mng_get_currentframe    %d\n", mng_get_currentframe    (mng_view->MNG_handle));
    printf("mng_get_currentlayer    %d\n", mng_get_currentlayer    (mng_view->MNG_handle));
    printf("mng_get_currentplaytime %d\n", mng_get_currentplaytime (mng_view->MNG_handle));
    printf("mng_get_totalframes     %d\n", mng_get_totalframes     (mng_view->MNG_handle));
    printf("mng_get_totallayers     %d\n", mng_get_totallayers     (mng_view->MNG_handle));
    printf("mng_get_totalplaytime   %d\n", mng_get_totalplaytime   (mng_view->MNG_handle));
    return TRUE;
}
