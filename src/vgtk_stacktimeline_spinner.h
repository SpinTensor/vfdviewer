#ifndef VGTK_STACKTIMELINE_SPINNER
#define VGTK_STACKTIMELINE_SPINNER

void vgtk_build_main_stacktimeline_spinner(GtkBuilder *builder);

double stacktimeline_xzoom_spinner_get_value();

void stacktimeline_xzoom_spinner_set_value(double value);

double stacktimeline_yzoom_spinner_get_value();

#endif
