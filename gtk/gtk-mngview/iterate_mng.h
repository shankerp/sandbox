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

#ifndef __GTK_MNG_VIEW_H__
#define __GTK_MNG_VIEW_H__

#include <libmng.h>
#include <gtk/gtk.h>

#define GTK_MNG_VIEW_TYPE               (gtk_mng_view_get_type ())
#define GTK_MNG_VIEW(obj)               (G_TYPE_CHECK_INSTANCE_CAST((obj), GTK_MNG_VIEW_TYPE, GtkMngView))
#define GTK_MNG_VIEW_CLASS(klass)       (G_TYPE_CHECK_CLASS_CAST((klass), GTK_MNG_VIEW_TYPE, GtkMngViewClass))
#define IS_GTK_MNG_VIEW(obj)            (G_TYPE_CHECK_INSTANCE_TYPE((obj), GTK_MNG_VIEW_TYPE))
#define IS_GTK_MNG_VIEW_CLASS(klass)    (G_TYPE_CHECK_CLASS_TYPE((klass), GTK_MNG_VIEW_TYPE))
#define GTK_MNG_VIEW_GET_CLASS(obj)     (G_TYPE_INSTANCE_GET_CLASS((obj),  GTK_MNG_VIEW_TYPE, GtkMngViewClass))

typedef struct _GtkMngView GtkMngView;
typedef struct _GtkMngViewClass GtkMngViewClass;

struct _GtkMngView
{
  GtkWidget widget;
  /* private */
  GTimer * timer;
  guint timeout_ID;
  guint width;
  guint height;
  mng_handle MNG_handle;
  guchar * MNG_drawing_buffer;
  guchar * MNG_alpha_buffer;
  guchar * mng_food;
  guint bytes_to_eat;
  guint bytes_eaten;
};

struct _GtkMngViewClass
{
  GtkWidgetClass klass;
};

GType gtk_mng_view_get_type (void);
GtkMngView * gtk_mng_view_new (void);

/* returns !FALSE on success */
gboolean gtk_mng_view_load_mng_from_memory (GtkMngView *, guchar *, guint);

#endif /* __GTK_MNG_VIEW_H__ */
