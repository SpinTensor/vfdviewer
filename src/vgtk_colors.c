#include <stdio.h>

#include "vgtk_colors.h"

#define CNORM 255.0

#define NCOLORS 41

const int vgtk_ncolors = NCOLORS;

vgtk_color_t vgtk_color_list[NCOLORS] = {
   {//
      .red = 0x10/CNORM,
      .green = 0x12/CNORM,
      .blue = 0x1c/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x2c/CNORM,
      .green = 0x1e/CNORM,
      .blue = 0x31/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x6b/CNORM,
      .green = 0x26/CNORM,
      .blue = 0x43/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xac/CNORM,
      .green = 0x28/CNORM,
      .blue = 0x47/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xec/CNORM,
      .green = 0x27/CNORM,
      .blue = 0x3f/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x94/CNORM,
      .green = 0x49/CNORM,
      .blue = 0x3a/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xde/CNORM,
      .green = 0x5d/CNORM,
      .blue = 0x3a/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xe9/CNORM,
      .green = 0x85/CNORM,
      .blue = 0x37/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xf3/CNORM,
      .green = 0xa8/CNORM,
      .blue = 0x33/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x4d/CNORM,
      .green = 0x35/CNORM,
      .blue = 0x33/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x6e/CNORM,
      .green = 0x4c/CNORM,
      .blue = 0x30/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xa2/CNORM,
      .green = 0x6d/CNORM,
      .blue = 0x3f/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xce/CNORM,
      .green = 0x92/CNORM,
      .blue = 0x48/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xda/CNORM,
      .green = 0xb1/CNORM,
      .blue = 0x63/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xe8/CNORM,
      .green = 0xd2/CNORM,
      .blue = 0x82/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xf7/CNORM,
      .green = 0xf3/CNORM,
      .blue = 0xb7/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x1e/CNORM,
      .green = 0x40/CNORM,
      .blue = 0x44/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x00/CNORM,
      .green = 0x65/CNORM,
      .blue = 0x54/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x26/CNORM,
      .green = 0x85/CNORM,
      .blue = 0x4c/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x5a/CNORM,
      .green = 0xb5/CNORM,
      .blue = 0x52/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x9d/CNORM,
      .green = 0xe6/CNORM,
      .blue = 0x4e/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x00/CNORM,
      .green = 0x8b/CNORM,
      .blue = 0x8b/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x62/CNORM,
      .green = 0xa4/CNORM,
      .blue = 0x77/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xa6/CNORM,
      .green = 0xcb/CNORM,
      .blue = 0x96/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xd3/CNORM,
      .green = 0xee/CNORM,
      .blue = 0xd3/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x3e/CNORM,
      .green = 0x3b/CNORM,
      .blue = 0x65/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x38/CNORM,
      .green = 0x59/CNORM,
      .blue = 0xb3/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x33/CNORM,
      .green = 0x88/CNORM,
      .blue = 0xde/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x36/CNORM,
      .green = 0xc5/CNORM,
      .blue = 0xf4/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x6d/CNORM,
      .green = 0xea/CNORM,
      .blue = 0xd6/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x5e/CNORM,
      .green = 0x5b/CNORM,
      .blue = 0x8c/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x8c/CNORM,
      .green = 0x78/CNORM,
      .blue = 0xa5/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xb0/CNORM,
      .green = 0xa7/CNORM,
      .blue = 0xb8/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xde/CNORM,
      .green = 0xce/CNORM,
      .blue = 0xed/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0x9a/CNORM,
      .green = 0x4d/CNORM,
      .blue = 0x76/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xc8/CNORM,
      .green = 0x78/CNORM,
      .blue = 0xaf/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xcc/CNORM,
      .green = 0x99/CNORM,
      .blue = 0xff/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xfa/CNORM,
      .green = 0x6e/CNORM,
      .blue = 0x79/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xff/CNORM,
      .green = 0xa2/CNORM,
      .blue = 0xac/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xff/CNORM,
      .green = 0xd1/CNORM,
      .blue = 0xd5/CNORM,
      .alpha = 0xff/CNORM
   },
   {//
      .red = 0xf6/CNORM,
      .green = 0xe8/CNORM,
      .blue = 0xe0/CNORM,
      .alpha = 0xff/CNORM
   }
};

#undef NCOLORS

vgtk_color_t vgtk_color2grayscale(vgtk_color_t color) {
   vgtk_color_t greyscale;
   greyscale.name  = "GreyScale";
   greyscale.red   = 0.2126 * color.red + 0.7152 * color.green + 0.0722 * color.blue;
   greyscale.green = 0.2126 * color.red + 0.7152 * color.green + 0.0722 * color.blue;
   greyscale.blue  = 0.2126 * color.red + 0.7152 * color.green + 0.0722 * color.blue;
   greyscale.alpha = color.alpha;
   return greyscale;
}

#define NCOLORS 11
const int vgtk_color_gradient_steps = NCOLORS;

vgtk_color_t vgtk_color_gradient(double value) {
   static const double colors[NCOLORS][3] = {
      {254.0/CNORM,  39.0/CNORM,  18.0/CNORM},
      {253.0/CNORM,  83.0/CNORM,   8.0/CNORM},
      {251.0/CNORM, 153.0/CNORM,   2.0/CNORM},
      {250.0/CNORM, 188.0/CNORM,   2.0/CNORM},
      {254.0/CNORM, 254.0/CNORM,  51.0/CNORM},
      {208.0/CNORM, 234.0/CNORM,  43.0/CNORM},
      {102.0/CNORM, 176.0/CNORM,  50.0/CNORM},
      {  3.0/CNORM, 146.0/CNORM, 206.0/CNORM},
      {  2.0/CNORM,  71.0/CNORM, 254.0/CNORM},
      { 61.0/CNORM,   1.0/CNORM, 164.0/CNORM},
      {134.0/CNORM,   1.0/CNORM, 175.0/CNORM}
   };

   // ensure correct values for value
   value = (value < 1.0) ? value : 1.0;
   value = (value > 0.0) ? value : 0.0;

   // Determine the two colors for mixing
   double scalevalue = value*(NCOLORS-1);
   fprintf(stderr, "value: %lf -> %lf\n", value, scalevalue);
   int lidx = scalevalue;
   fprintf(stderr, "lidx: %d\n", lidx);
   if (lidx == NCOLORS-1) {
      lidx--;
      fprintf(stderr, "   (lidx: %d)\n", lidx);
   }
   int hidx = lidx + 1;
   fprintf(stderr, "hidx: %d\n", hidx);

   double s = scalevalue - (double) lidx;
   fprintf(stderr, "s = %lf, (1-s) = %lf\n", s, 1.0-s);
   vgtk_color_t color;
   color.red   = s*colors[hidx][0] + (1.0-s)*colors[lidx][0];
   color.green = s*colors[hidx][1] + (1.0-s)*colors[lidx][1];
   color.blue  = s*colors[hidx][2] + (1.0-s)*colors[lidx][2];
   fprintf(stderr, "rgb = (%lf, %lf, %lf)\n\n", color.red, color.green, color.blue);
   color.alpha = 1.0;

   return color;
#undef NCOLORS
}


#undef CNORM
