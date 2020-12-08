#ifndef VGTK_COLORS
#define VGTK_COLORS

typedef struct {
   char *name;
   double red;
   double green;
   double blue;
   double alpha;
} vgtk_color_t;

extern const int vgtk_ncolors;

extern vgtk_color_t vgtk_color_list[];

#endif
