#ifndef VGTK_DRAW_TYPES
#define VGTK_DRAW_TYPES

#include <stdbool.h>

typedef struct {
   double red;
   double green;
   double blue;
   double alpha;
} vgtk_color_t;

typedef struct {
   vgtk_color_t color;
   double xmin;
   double xmax;
   double ymin;
   double ymax;
   bool filled;
} vgtk_rectangle_t;

#endif
