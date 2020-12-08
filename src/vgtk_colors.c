#include "vgtk_draw_types.h"

#define CNORM 255.0

const vgtk_color_t vgtk_color_white = {
   .red = 255.0/CNORM,
   .green = 255.0/CNORM,
   .blue = 255.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_silver = {
   .red = 192.0/CNORM,
   .green = 192.0/CNORM,
   .blue = 192.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_gray = {
   .red = 128.0/CNORM,
   .green = 128.0/CNORM,
   .blue = 128.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_black = {
   .red = 0.0/CNORM,
   .green = 0.0/CNORM,
   .blue = 0.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_red = {
   .red = 255.0/CNORM,
   .green = 0.0/CNORM,
   .blue = 0.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_maroon = {
   .red = 128.0/CNORM,
   .green = 0.0/CNORM,
   .blue = 0.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_yellow = {
   .red = 255.0/CNORM,
   .green = 255.0/CNORM,
   .blue = 0.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_olive = {
   .red = 128.0/CNORM,
   .green = 128.0/CNORM,
   .blue = 0.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_lime = {
   .red = 0.0/CNORM,
   .green = 255.0/CNORM,
   .blue = 0.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_green = {
   .red = 0.0/CNORM,
   .green = 128.0/CNORM,
   .blue = 0.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_aqua = {
   .red = 0.0/CNORM,
   .green = 255.0/CNORM,
   .blue = 255.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_teal = {
   .red = 0.0/CNORM,
   .green = 128.0/CNORM,
   .blue = 128.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_blue = {
   .red = 0.0/CNORM,
   .green = 0.0/CNORM,
   .blue = 255.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_navy = {
   .red = 0.0/CNORM,
   .green = 0.0/CNORM,
   .blue = 128.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_fuchsia = {
   .red = 255.0/CNORM,
   .green = 0.0/CNORM,
   .blue = 255.0/CNORM,
   .alpha = 255.0/CNORM
};

const vgtk_color_t vgtk_color_purple = {
   .red = 128.0/CNORM,
   .green = 0.0/CNORM,
   .blue = 128.0/CNORM,
   .alpha = 255.0/CNORM
};

#define NCOLORS 16

const int vgtk_ncolors = NCOLORS;

vgtk_color_t vgtk_color_list[] = {
   vgtk_color_white,
   vgtk_color_silver,
   vgtk_color_gray,
   vgtk_color_black,
   vgtk_color_red,
   vgtk_color_maroon,
   vgtk_color_yellow,
   vgtk_color_olive,
   vgtk_color_lime,
   vgtk_color_green,
   vgtk_color_aqua,
   vgtk_color_teal,
   vgtk_color_blue,
   vgtk_color_navy,
   vgtk_color_fuchsia,
   vgtk_color_purple
};

#undef NCOLORS

#undef CNORM
