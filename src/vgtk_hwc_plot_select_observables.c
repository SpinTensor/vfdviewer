#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <gtk/gtk.h>

#include "vgtk_hwc_plot.h"
#include "vfd_list.h"

// some callback definitions
void on_hwc_plot_derived_counters_formula_entry_activate(
   GtkEntry *entry,
   gpointer user_data);

void on_hwc_plot_derived_counters_observablename_entry_activate(
   GtkEntry *entry,
   gpointer user_data);

gboolean vgtk_hwc_plot_derived_counters_formula_entry_query_tooltip_callback(
   GtkWidget *widget,
   gint x, gint y,
   gboolean keyboard,
   GtkTooltip *tooltip,
   gpointer data);

GtkComboBoxText *hwc_plot_derived_counters_select_counter_comboboxtext = NULL;
GtkEntry *hwc_plot_derived_counters_formula_entry = NULL;
GtkEntry *hwc_plot_derived_counters_observablename_entry = NULL;

void vgtk_build_hwc_select_observables(GtkBuilder *builder) {
   hwc_plot_derived_counters_select_counter_comboboxtext = GTK_COMBO_BOX_TEXT(
      gtk_builder_get_object(builder, "hwc_plot_derived_counters_select_counter_comboboxtext"));

   hwc_plot_derived_counters_formula_entry = GTK_ENTRY(
      gtk_builder_get_object(builder, "hwc_plot_derived_counters_formula_entry"));
   // define the tooltip
   gtk_widget_set_has_tooltip(GTK_WIDGET(hwc_plot_derived_counters_formula_entry), TRUE);
   g_signal_connect(hwc_plot_derived_counters_formula_entry,
                    "query-tooltip",
                    G_CALLBACK(vgtk_hwc_plot_derived_counters_formula_entry_query_tooltip_callback),
                    NULL);

   hwc_plot_derived_counters_observablename_entry = GTK_ENTRY(
      gtk_builder_get_object(builder, "hwc_plot_derived_counters_observablename_entry"));

   gtk_builder_connect_signals(builder, NULL);
}

const char *vgtk_hwc_plot_derived_counters_formula_entry_get_text() {
   return gtk_entry_get_text(hwc_plot_derived_counters_formula_entry);
}

const char *vgtk_hwc_plot_derived_counters_observablename_entry_get_text() {
   return gtk_entry_get_text(hwc_plot_derived_counters_observablename_entry);
}

#define CUSTOM_EXPRESSION_STRING "custom"
void set_hwc_plot_derived_counters_select_counter_comboboxtext_options() {
   // empty existing options from comboboxtext
   gtk_combo_box_text_remove_all(hwc_plot_derived_counters_select_counter_comboboxtext);

   // add the default option
   int noptions = 0;
   int max_options = 16;
   char **optlist = (char**) malloc(max_options*sizeof(char*));
   optlist[noptions] = CUSTOM_EXPRESSION_STRING;
   noptions++;

   // go over all vfds and add the options
   vfd_t *vfdtrace = first_vfd();
   while (vfdtrace != NULL) {
      int vfdopts = vfdtrace->hwc_header->n_formulae;
      for (int iopt=0; iopt<vfdopts; iopt++) {
         // check if the vfd-expression is not already contained in the list
         bool new_opt = true;
         for (int jopt=0; jopt<noptions; jopt++) {
            if (!strcmp(optlist[jopt], vfdtrace->hwc_header->scen_expr_names[iopt])) {
               new_opt = false;
               break;
            }
         }

         // option is new. add it to the list
         if (new_opt) {
            // check if reallocation is required.
            if (noptions == max_options) {
               max_options *= 1.4;
               optlist = (char**) realloc(optlist, max_options*sizeof(char*));
            }

            optlist[noptions] = vfdtrace->hwc_header->scen_expr_names[iopt];
            noptions++;
         }
      }

      vfdtrace = vfdtrace->next;
   }

   // list all options in the coboboxtext dropdown menu
   for (int jopt=0; jopt<noptions; jopt++) {
      gtk_combo_box_text_append(
         hwc_plot_derived_counters_select_counter_comboboxtext,
         NULL,
         optlist[jopt]);
#ifdef __DEBUG
      fprintf(stderr, "HWC plot expression select\n");
      fprintf(stderr, "      %2d: %s\n", jopt, optlist[jopt]);
#endif
   }

   free(optlist);

   gtk_combo_box_set_active(GTK_COMBO_BOX(
      hwc_plot_derived_counters_select_counter_comboboxtext), 0);
}

// callback functions
void on_hwc_plot_derived_counters_select_counter_comboboxtext_changed(
   GtkComboBox *widget,
   gpointer user_data) {
   (void) user_data;

   const char *sel_text = gtk_combo_box_text_get_active_text(
      GTK_COMBO_BOX_TEXT(widget));

   if (sel_text != NULL) {
      if (!strcmp(sel_text, CUSTOM_EXPRESSION_STRING)) {
         gtk_entry_set_text(hwc_plot_derived_counters_formula_entry,
                            "");
         gtk_entry_set_text(hwc_plot_derived_counters_observablename_entry,
                            "");
      } else {
         // go over all vfds and add the options
         bool found_formula = false;
         vfd_t *vfdtrace = first_vfd();
         while (vfdtrace != NULL && !found_formula) {
            int vfdopts = vfdtrace->hwc_header->n_formulae;
            for (int iopt=0; iopt<vfdopts; iopt++) {
               if (!strcmp(sel_text, vfdtrace->hwc_header->scen_expr_names[iopt])) {
                  gtk_entry_set_text(
                     hwc_plot_derived_counters_formula_entry,
                     vfdtrace->hwc_header->scen_expr_formulae[iopt]);
                  gtk_entry_set_text(
                     hwc_plot_derived_counters_observablename_entry,
                     vfdtrace->hwc_header->scen_expr_names[iopt]);
                  found_formula = true;
                  break;
               }
            }
         }

         if (!found_formula) {
            gtk_entry_set_text(hwc_plot_derived_counters_formula_entry,
                               "");
            gtk_entry_set_text(hwc_plot_derived_counters_observablename_entry,
                               "");
         }
      }
      on_hwc_plot_derived_counters_formula_entry_activate(
         hwc_plot_derived_counters_formula_entry, NULL);
      on_hwc_plot_derived_counters_observablename_entry_activate(
         hwc_plot_derived_counters_observablename_entry, NULL);
   }
}
#undef CUSTOM_EXPRESSION_STRING

void on_hwc_plot_derived_counters_formula_entry_activate(
   GtkEntry *entry,
   gpointer user_data) {
   (void) entry;
   (void) user_data;

   vgtk_hwc_plot_update();

}

void on_hwc_plot_derived_counters_observablename_entry_activate(
   GtkEntry *entry,
   gpointer  user_data) {
   (void) user_data;

   const char *text = gtk_entry_get_text(entry);
   vgtk_hwc_set_plot_yaxis_title(text);
}

gboolean vgtk_hwc_plot_derived_counters_formula_entry_query_tooltip_callback(
   GtkWidget *widget,
   gint x, gint y,
   gboolean keyboard,
   GtkTooltip *tooltip,
   gpointer data) {

   (void) widget;
   (void) x;
   (void) y;
   (void) keyboard;
   (void) data;

   // create a list of unique hwc variables
   int nhwcs = 0;
   int max_hwcs = 16;
   char **hw_names = (char**) malloc(max_hwcs*sizeof(char*));
   char **te_names = (char**) malloc(max_hwcs*sizeof(char*));
   hw_names[nhwcs] = "runtime";
   te_names[nhwcs] = "t";
   nhwcs++;

   // go over all vfds and add the variable names and their tiny expression name
   vfd_t *vfdtrace = first_vfd();
   while (vfdtrace != NULL) {
      int vfdhwcs = vfdtrace->hwc_header->n_hw_obs;
      for (int ihwc=0; ihwc<vfdhwcs; ihwc++) {
         // check if hwc is not already contained in the list
         bool new_hwc = true;
         for (int jhwc=0; jhwc<nhwcs; jhwc++) {
            if (!strcmp(hw_names[jhwc], vfdtrace->hwc_header->hw_obs_names[ihwc])) {
               new_hwc = false;
               break;
            }
         }

         // hwc is new. add it to the list
         if (new_hwc) {
            // check if reallocation is required
            if (nhwcs == max_hwcs) {
               max_hwcs *= 1.4;
               hw_names = (char**) realloc(hw_names, max_hwcs*sizeof(char*));
               te_names = (char**) realloc(te_names, max_hwcs*sizeof(char*));
            }

            hw_names[nhwcs] = vfdtrace->hwc_header->hw_obs_names[ihwc];
            te_names[nhwcs] = vfdtrace->hwc_header->te_var_names[ihwc];
            nhwcs++;
         }
      }

      vfdtrace = vfdtrace->next;
   }

   if (nhwcs > 0) {
      // go through all hardware counter names
      // and record their length
      int sumstrlen = 0;
      for (int ihwc=0; ihwc<nhwcs; ihwc++) {
         // format is "\nhw_name: te_name" per line
         sumstrlen += strlen(hw_names[ihwc]);
         sumstrlen += strlen(te_names[ihwc]);
         sumstrlen += 3; // "\n" and ": "
      }

      // Add some header text:
#define HWC_TOOLTIP_HEADER_TEXT "Available variables\n(name: variable)"
      sumstrlen += strlen(HWC_TOOLTIP_HEADER_TEXT);
      // add null terminator space
      sumstrlen ++;
      // allocate memory and build the tooltip string
      char *tooltipstr = (char*) malloc(sumstrlen*sizeof(char));
      char *tooltipstr_ptr = tooltipstr;

      // first the header text
      strcpy(tooltipstr_ptr, HWC_TOOLTIP_HEADER_TEXT);
      tooltipstr_ptr += strlen(HWC_TOOLTIP_HEADER_TEXT);
#undef HWC_TOOLTIP_HEADER_TEXT

      // next all the hwc variables
      for (int ihwc=0; ihwc<nhwcs; ihwc++) {
         strcpy(tooltipstr_ptr, "\n");
         tooltipstr_ptr ++;
         strcpy(tooltipstr_ptr, hw_names[ihwc]);
         tooltipstr_ptr += strlen(hw_names[ihwc]);
         strcpy(tooltipstr_ptr, ": ");
         tooltipstr_ptr += 2;
         strcpy(tooltipstr_ptr, te_names[ihwc]);
         tooltipstr_ptr += strlen(te_names[ihwc]);
      }

      gtk_tooltip_set_text(tooltip, tooltipstr);

      free(tooltipstr);
      tooltipstr = NULL;
      tooltipstr_ptr = NULL;

      free(hw_names);
      hw_names = NULL;
      free(te_names);
      te_names = NULL;

      return TRUE;
   } else {
      return FALSE;
   }
}
