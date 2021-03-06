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

vgtk_color_t vgtk_color2grayscale(vgtk_color_t color);

extern const int vgtk_color_gradient_steps;
vgtk_color_t vgtk_color_gradient(double value);

#endif
