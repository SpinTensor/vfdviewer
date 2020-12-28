#include <stdlib.h>
#include <stdbool.h>

#include <gtk/gtk.h>

#include "vfd_types.h"
#include "vfd_list.h"
#include "vgtk_colors.h"
#include "vgtk_comm_matrix_grid.h"
#include "vgtk_comm_matrix_mode_switcher.h"
#include "vgtk_comm_matrix_legend.h"
#include "vgtk_stacktimeline_entry.h"
#include "vgtk_comm_matrix_update_bw.h"
#include "vgtk_comm_matrix_update_size.h"
#include "vgtk_comm_matrix_update_count.h"
#include "vgtk_comm_matrix_cursorpos_labels.h"

GtkDrawingArea *comm_matrix_matrix_drawing_area = NULL;
cairo_surface_t *comm_matrix_matrix_drawing_surface = NULL;

static int comm_matrix_nprocs = 0;
bool comm_matrix_valid = false;
double *comm_matrix_data = NULL;
double comm_matrix_inorm = 0.0;

void vgtk_build_comm_matrix(GtkBuilder *builder) {
   comm_matrix_matrix_drawing_area = GTK_DRAWING_AREA(
      gtk_builder_get_object(builder, "comm_matrix_matrix_drawing_area"));

   vgtk_build_comm_matrix_cursorpos_labels(builder);

   // allow button press events for drawing area
   gtk_widget_set_events(GTK_WIDGET(comm_matrix_matrix_drawing_area),
                         gtk_widget_get_events(GTK_WIDGET(
                            comm_matrix_matrix_drawing_area))
                         | GDK_BUTTON_PRESS_MASK);

   gtk_builder_connect_signals(builder, NULL);
}

void comm_matrix_update() {
   // Get the number of total processes
   int nprocs = vfds_nprocs();

   if (nprocs != comm_matrix_nprocs) {
      // matrix size changed since last update
      if (comm_matrix_data != NULL) {
         free(comm_matrix_data);
         comm_matrix_data = NULL;
      }
      comm_matrix_data = (double*) malloc(nprocs*nprocs*sizeof(double));
      comm_matrix_nprocs = nprocs;
   }

   // update the data based on the selected metric
   comm_matrix_unit_t unit = comm_matrix_get_unit();
   comm_matrix_mode_t metric = comm_matrix_get_metric_mode();
   switch(unit) {
      case cm_bw:
         switch(metric) {
            case cm_max:
               comm_matrix_update_bw_max(comm_matrix_nprocs,
                                         comm_matrix_data,
                                         &comm_matrix_inorm);
               break;
            case cm_avg:
               comm_matrix_update_bw_avg(comm_matrix_nprocs,
                                         comm_matrix_data,
                                         &comm_matrix_inorm);
               break;
            case cm_min:
               comm_matrix_update_bw_min(comm_matrix_nprocs,
                                         comm_matrix_data,
                                         &comm_matrix_inorm);
               break;
         }
         break;
      case cm_size:
         switch(metric) {
            case cm_max:
               comm_matrix_update_size_max(comm_matrix_nprocs,
                                           comm_matrix_data,
                                           &comm_matrix_inorm);
               break;
            case cm_avg:
               comm_matrix_update_size_avg(comm_matrix_nprocs,
                                           comm_matrix_data,
                                           &comm_matrix_inorm);
               break;
            case cm_min:
               comm_matrix_update_size_min(comm_matrix_nprocs,
                                           comm_matrix_data,
                                           &comm_matrix_inorm);
               break;
         }
         break;
      case cm_count:
         comm_matrix_update_count(comm_matrix_nprocs,
                                  comm_matrix_data,
                                  &comm_matrix_inorm);
         break;
   }


   // validate comm matrix
   comm_matrix_valid = true;
}

void vgtk_draw_comm_matrix(cairo_t *cr) {
   // Get the number of total processes
   int nprocs = vfds_nprocs();

   // update the comm matrix if necessary
   if (!comm_matrix_valid) {
      comm_matrix_update();
   }

   GtkDrawingArea *drawing_area = comm_matrix_matrix_drawing_area;

   // get surface dimensions
   int sfwidth = gtk_widget_get_allocated_width(GTK_WIDGET(drawing_area));
   int sfheight = gtk_widget_get_allocated_height(GTK_WIDGET(drawing_area));

   double rect_width = (double) sfwidth / ((double) nprocs);
   double rect_height = (double) sfheight / ((double) nprocs);

   for (int icol=0; icol<nprocs; icol++) {
      for (int irow=0; irow<nprocs; irow++) {
         double value = comm_matrix_data[irow*nprocs+icol];
         vgtk_color_t color;
         if (value > 0.0) {
            color = vgtk_color_gradient(value);
         } else {
            color.red   = 195.0/255.0;
            color.green = 195.0/255.0;
            color.blue  = 195.0/255.0;
            color.alpha = 1.0;
         }

         cairo_set_source_rgba(cr,
                               color.red,
                               color.green,
                               color.blue,
                               color.alpha);
         cairo_rectangle(cr,
                         icol*rect_width, (nprocs-irow-1)*rect_height,
                         rect_width, rect_height);
         cairo_fill_preserve(cr);

         cairo_set_source_rgba(cr,
                               195.0/255.0,
                               195.0/255.0,
                               195.0/255.0,
                               0.5);
         cairo_stroke(cr);

      }
   }
}

void comm_matrix_invalidate() {
   comm_matrix_valid = false;
}

void comm_matrix_redraw() {
   cairo_t *cr;
   cr = cairo_create (comm_matrix_matrix_drawing_surface);
   vgtk_draw_comm_matrix(cr);
   cairo_destroy(cr);
   // actually draw the queued actions
   gtk_widget_queue_draw(GTK_WIDGET(comm_matrix_matrix_drawing_area));
}

// Callback functions for the communication matrix drawing area
gboolean on_comm_matrix_matrix_drawing_area_configure_event(
   GtkWidget *widget,
   GdkEventConfigure *event,
   gpointer data) {

   (void) event;
   (void) data;

   if (comm_matrix_matrix_drawing_surface != NULL) {
      cairo_surface_destroy(comm_matrix_matrix_drawing_surface);
   }

   comm_matrix_matrix_drawing_surface = gdk_window_create_similar_surface(
      gtk_widget_get_window(widget),
      CAIRO_CONTENT_COLOR,
      gtk_widget_get_allocated_width(widget),
      gtk_widget_get_allocated_height(widget));

   vgtk_comm_matrix_set_proc_labels(vfds_nprocs());

   return TRUE;
}

gboolean on_comm_matrix_matrix_drawing_area_draw(
   GtkWidget *widget,
   cairo_t *cr,
   gpointer data) {
   (void) widget;
   (void) data;

   vgtk_draw_comm_matrix(cr);

   return TRUE;
}

// callback function for left mouse button press on drawing area
void on_comm_matrix_matrix_drawing_area_button_press_event(
   GtkWidget *widget,
   GdkEventButton *event,
   gpointer data) {

   (void) widget;
   (void) data;

   GtkDrawingArea *drawing_area = comm_matrix_matrix_drawing_area;
   // get surface dimensions
   int sfwidth = gtk_widget_get_allocated_width(GTK_WIDGET(drawing_area));
   int sfheight = gtk_widget_get_allocated_height(GTK_WIDGET(drawing_area));

   // Get the number of total processes
   int nprocs = comm_matrix_nprocs;
   // get mouse cursor position
   int send_rank = nprocs * (event->x / sfwidth);
   int recv_rank = nprocs * (1.0 - (event->y / sfheight));

   // get value from communication matrix
   int idx = recv_rank*nprocs + send_rank;
   double value = comm_matrix_data[idx] * comm_matrix_inorm;

   // set the cursor pos label
   set_comm_matrix_cursorpos_label(send_rank, recv_rank, value);
}
