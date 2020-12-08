#include "vgtk_colors.h"

#define CNORM 255.0

#define NCOLORS 143

const int vgtk_ncolors = NCOLORS;

vgtk_color_t vgtk_color_list[NCOLORS] = {
   {// IndianRed
      .name = "IndianRed",
      .red = 205.0/CNORM,
      .green = 92.0/CNORM,
      .blue = 92.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightCoral
      .name = "LightCoral",
      .red = 240.0/CNORM,
      .green = 128.0/CNORM,
      .blue = 128.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Salmon
      .name = "Salmon",
      .red = 250.0/CNORM,
      .green = 128.0/CNORM,
      .blue = 114.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkSalmon
      .name = "DarkSalmon",
      .red = 233.0/CNORM,
      .green = 150.0/CNORM,
      .blue = 122.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightSalmon
      .name = "LightSalmon",
      .red = 255.0/CNORM,
      .green = 160.0/CNORM,
      .blue = 122.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Crimson
      .name = "Crimson",
      .red = 220.0/CNORM,
      .green = 20.0/CNORM,
      .blue = 60.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Red
      .name = "Red",
      .red = 255.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// FireBrick
      .name = "FireBrick",
      .red = 178.0/CNORM,
      .green = 34.0/CNORM,
      .blue = 34.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkRed
      .name = "DarkRed",
      .red = 139.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Pink
      .name = "Pink",
      .red = 255.0/CNORM,
      .green = 192.0/CNORM,
      .blue = 203.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightPink
      .name = "LightPink",
      .red = 255.0/CNORM,
      .green = 182.0/CNORM,
      .blue = 193.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// HotPink
      .name = "HotPink",
      .red = 255.0/CNORM,
      .green = 105.0/CNORM,
      .blue = 180.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DeepPink
      .name = "DeepPink",
      .red = 255.0/CNORM,
      .green = 20.0/CNORM,
      .blue = 147.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MediumVioletRed
      .name = "MediumVioletRed",
      .red = 199.0/CNORM,
      .green = 21.0/CNORM,
      .blue = 133.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// PaleVioletRed
      .name = "PaleVioletRed",
      .red = 219.0/CNORM,
      .green = 112.0/CNORM,
      .blue = 147.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightSalmon
      .name = "LightSalmon",
      .red = 255.0/CNORM,
      .green = 160.0/CNORM,
      .blue = 122.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Coral
      .name = "Coral",
      .red = 255.0/CNORM,
      .green = 127.0/CNORM,
      .blue = 80.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Tomato
      .name = "Tomato",
      .red = 255.0/CNORM,
      .green = 99.0/CNORM,
      .blue = 71.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// OrangeRed
      .name = "OrangeRed",
      .red = 255.0/CNORM,
      .green = 69.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkOrange
      .name = "DarkOrange",
      .red = 255.0/CNORM,
      .green = 140.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Orange
      .name = "Orange",
      .red = 255.0/CNORM,
      .green = 165.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Gold
      .name = "Gold",
      .red = 255.0/CNORM,
      .green = 215.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Yellow
      .name = "Yellow",
      .red = 255.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightYellow
      .name = "LightYellow",
      .red = 255.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 224.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LemonChiffon
      .name = "LemonChiffon",
      .red = 255.0/CNORM,
      .green = 250.0/CNORM,
      .blue = 205.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightGoldenrodYellow
      .name = "LightGoldenrodYellow",
      .red = 250.0/CNORM,
      .green = 250.0/CNORM,
      .blue = 210.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// PapayaWhip
      .name = "PapayaWhip",
      .red = 255.0/CNORM,
      .green = 239.0/CNORM,
      .blue = 213.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Moccasin
      .name = "Moccasin",
      .red = 255.0/CNORM,
      .green = 228.0/CNORM,
      .blue = 181.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// PeachPuff
      .name = "PeachPuff",
      .red = 255.0/CNORM,
      .green = 218.0/CNORM,
      .blue = 185.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// PaleGoldenrod
      .name = "PaleGoldenrod",
      .red = 238.0/CNORM,
      .green = 232.0/CNORM,
      .blue = 170.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Khaki
      .name = "Khaki",
      .red = 240.0/CNORM,
      .green = 230.0/CNORM,
      .blue = 140.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkKhaki
      .name = "DarkKhaki",
      .red = 189.0/CNORM,
      .green = 183.0/CNORM,
      .blue = 107.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Lavender
      .name = "Lavender",
      .red = 230.0/CNORM,
      .green = 230.0/CNORM,
      .blue = 250.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Thistle
      .name = "Thistle",
      .red = 216.0/CNORM,
      .green = 191.0/CNORM,
      .blue = 216.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Plum
      .name = "Plum",
      .red = 221.0/CNORM,
      .green = 160.0/CNORM,
      .blue = 221.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Violet
      .name = "Violet",
      .red = 238.0/CNORM,
      .green = 130.0/CNORM,
      .blue = 238.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Orchid
      .name = "Orchid",
      .red = 218.0/CNORM,
      .green = 112.0/CNORM,
      .blue = 214.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Fuchsia
      .name = "Fuchsia",
      .red = 255.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 255.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Magenta
      .name = "Magenta",
      .red = 255.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 255.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MediumOrchid
      .name = "MediumOrchid",
      .red = 186.0/CNORM,
      .green = 85.0/CNORM,
      .blue = 211.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MediumPurple
      .name = "MediumPurple",
      .red = 147.0/CNORM,
      .green = 112.0/CNORM,
      .blue = 219.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// RebeccaPurple
      .name = "RebeccaPurple",
      .red = 102.0/CNORM,
      .green = 51.0/CNORM,
      .blue = 153.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// BlueViolet
      .name = "BlueViolet",
      .red = 138.0/CNORM,
      .green = 43.0/CNORM,
      .blue = 226.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkViolet
      .name = "DarkViolet",
      .red = 148.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 211.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkOrchid
      .name = "DarkOrchid",
      .red = 153.0/CNORM,
      .green = 50.0/CNORM,
      .blue = 204.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkMagenta
      .name = "DarkMagenta",
      .red = 139.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 139.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Purple
      .name = "Purple",
      .red = 128.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 128.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Indigo
      .name = "Indigo",
      .red = 75.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 130.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// SlateBlue
      .name = "SlateBlue",
      .red = 106.0/CNORM,
      .green = 90.0/CNORM,
      .blue = 205.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkSlateBlue
      .name = "DarkSlateBlue",
      .red = 72.0/CNORM,
      .green = 61.0/CNORM,
      .blue = 139.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MediumSlateBlue
      .name = "MediumSlateBlue",
      .red = 123.0/CNORM,
      .green = 104.0/CNORM,
      .blue = 238.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// GreenYellow
      .name = "GreenYellow",
      .red = 173.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 47.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Chartreuse
      .name = "Chartreuse",
      .red = 127.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LawnGreen
      .name = "LawnGreen",
      .red = 124.0/CNORM,
      .green = 252.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Lime
      .name = "Lime",
      .red = 0.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LimeGreen
      .name = "LimeGreen",
      .red = 50.0/CNORM,
      .green = 205.0/CNORM,
      .blue = 50.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// PaleGreen
      .name = "PaleGreen",
      .red = 152.0/CNORM,
      .green = 251.0/CNORM,
      .blue = 152.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightGreen
      .name = "LightGreen",
      .red = 144.0/CNORM,
      .green = 238.0/CNORM,
      .blue = 144.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MediumSpringGreen
      .name = "MediumSpringGreen",
      .red = 0.0/CNORM,
      .green = 250.0/CNORM,
      .blue = 154.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// SpringGreen
      .name = "SpringGreen",
      .red = 0.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 127.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MediumSeaGreen
      .name = "MediumSeaGreen",
      .red = 60.0/CNORM,
      .green = 179.0/CNORM,
      .blue = 113.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// SeaGreen
      .name = "SeaGreen",
      .red = 46.0/CNORM,
      .green = 139.0/CNORM,
      .blue = 87.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// ForestGreen
      .name = "ForestGreen",
      .red = 34.0/CNORM,
      .green = 139.0/CNORM,
      .blue = 34.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Green
      .name = "Green",
      .red = 0.0/CNORM,
      .green = 128.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkGreen
      .name = "DarkGreen",
      .red = 0.0/CNORM,
      .green = 100.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// YellowGreen
      .name = "YellowGreen",
      .red = 154.0/CNORM,
      .green = 205.0/CNORM,
      .blue = 50.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// OliveDrab
      .name = "OliveDrab",
      .red = 107.0/CNORM,
      .green = 142.0/CNORM,
      .blue = 35.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Olive
      .name = "Olive",
      .red = 128.0/CNORM,
      .green = 128.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkOliveGreen
      .name = "DarkOliveGreen",
      .red = 85.0/CNORM,
      .green = 107.0/CNORM,
      .blue = 47.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MediumAquamarine
      .name = "MediumAquamarine",
      .red = 102.0/CNORM,
      .green = 205.0/CNORM,
      .blue = 170.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkSeaGreen
      .name = "DarkSeaGreen",
      .red = 143.0/CNORM,
      .green = 188.0/CNORM,
      .blue = 139.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightSeaGreen
      .name = "LightSeaGreen",
      .red = 32.0/CNORM,
      .green = 178.0/CNORM,
      .blue = 170.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkCyan
      .name = "DarkCyan",
      .red = 0.0/CNORM,
      .green = 139.0/CNORM,
      .blue = 139.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Teal
      .name = "Teal",
      .red = 0.0/CNORM,
      .green = 128.0/CNORM,
      .blue = 128.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Aqua
      .name = "Aqua",
      .red = 0.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 255.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Cyan
      .name = "Cyan",
      .red = 0.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 255.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightCyan
      .name = "LightCyan",
      .red = 224.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 255.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// PaleTurquoise
      .name = "PaleTurquoise",
      .red = 175.0/CNORM,
      .green = 238.0/CNORM,
      .blue = 238.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Aquamarine
      .name = "Aquamarine",
      .red = 127.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 212.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Turquoise
      .name = "Turquoise",
      .red = 64.0/CNORM,
      .green = 224.0/CNORM,
      .blue = 208.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MediumTurquoise
      .name = "MediumTurquoise",
      .red = 72.0/CNORM,
      .green = 209.0/CNORM,
      .blue = 204.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkTurquoise
      .name = "DarkTurquoise",
      .red = 0.0/CNORM,
      .green = 206.0/CNORM,
      .blue = 209.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// CadetBlue
      .name = "CadetBlue",
      .red = 95.0/CNORM,
      .green = 158.0/CNORM,
      .blue = 160.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// SteelBlue
      .name = "SteelBlue",
      .red = 70.0/CNORM,
      .green = 130.0/CNORM,
      .blue = 180.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightSteelBlue
      .name = "LightSteelBlue",
      .red = 176.0/CNORM,
      .green = 196.0/CNORM,
      .blue = 222.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// PowderBlue
      .name = "PowderBlue",
      .red = 176.0/CNORM,
      .green = 224.0/CNORM,
      .blue = 230.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightBlue
      .name = "LightBlue",
      .red = 173.0/CNORM,
      .green = 216.0/CNORM,
      .blue = 230.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// SkyBlue
      .name = "SkyBlue",
      .red = 135.0/CNORM,
      .green = 206.0/CNORM,
      .blue = 235.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightSkyBlue
      .name = "LightSkyBlue",
      .red = 135.0/CNORM,
      .green = 206.0/CNORM,
      .blue = 250.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DeepSkyBlue
      .name = "DeepSkyBlue",
      .red = 0.0/CNORM,
      .green = 191.0/CNORM,
      .blue = 255.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DodgerBlue
      .name = "DodgerBlue",
      .red = 30.0/CNORM,
      .green = 144.0/CNORM,
      .blue = 255.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// CornflowerBlue
      .name = "CornflowerBlue",
      .red = 100.0/CNORM,
      .green = 149.0/CNORM,
      .blue = 237.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MediumSlateBlue
      .name = "MediumSlateBlue",
      .red = 123.0/CNORM,
      .green = 104.0/CNORM,
      .blue = 238.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// RoyalBlue
      .name = "RoyalBlue",
      .red = 65.0/CNORM,
      .green = 105.0/CNORM,
      .blue = 225.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Blue
      .name = "Blue",
      .red = 0.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 255.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MediumBlue
      .name = "MediumBlue",
      .red = 0.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 205.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkBlue
      .name = "DarkBlue",
      .red = 0.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 139.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Navy
      .name = "Navy",
      .red = 0.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 128.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MidnightBlue
      .name = "MidnightBlue",
      .red = 25.0/CNORM,
      .green = 25.0/CNORM,
      .blue = 112.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Cornsilk
      .name = "Cornsilk",
      .red = 255.0/CNORM,
      .green = 248.0/CNORM,
      .blue = 220.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// BlanchedAlmond
      .name = "BlanchedAlmond",
      .red = 255.0/CNORM,
      .green = 235.0/CNORM,
      .blue = 205.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Bisque
      .name = "Bisque",
      .red = 255.0/CNORM,
      .green = 228.0/CNORM,
      .blue = 196.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// NavajoWhite
      .name = "NavajoWhite",
      .red = 255.0/CNORM,
      .green = 222.0/CNORM,
      .blue = 173.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Wheat
      .name = "Wheat",
      .red = 245.0/CNORM,
      .green = 222.0/CNORM,
      .blue = 179.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// BurlyWood
      .name = "BurlyWood",
      .red = 222.0/CNORM,
      .green = 184.0/CNORM,
      .blue = 135.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Tan
      .name = "Tan",
      .red = 210.0/CNORM,
      .green = 180.0/CNORM,
      .blue = 140.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// RosyBrown
      .name = "RosyBrown",
      .red = 188.0/CNORM,
      .green = 143.0/CNORM,
      .blue = 143.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// SandyBrown
      .name = "SandyBrown",
      .red = 244.0/CNORM,
      .green = 164.0/CNORM,
      .blue = 96.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Goldenrod
      .name = "Goldenrod",
      .red = 218.0/CNORM,
      .green = 165.0/CNORM,
      .blue = 32.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkGoldenrod
      .name = "DarkGoldenrod",
      .red = 184.0/CNORM,
      .green = 134.0/CNORM,
      .blue = 11.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Peru
      .name = "Peru",
      .red = 205.0/CNORM,
      .green = 133.0/CNORM,
      .blue = 63.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Chocolate
      .name = "Chocolate",
      .red = 210.0/CNORM,
      .green = 105.0/CNORM,
      .blue = 30.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// SaddleBrown
      .name = "SaddleBrown",
      .red = 139.0/CNORM,
      .green = 69.0/CNORM,
      .blue = 19.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Sienna
      .name = "Sienna",
      .red = 160.0/CNORM,
      .green = 82.0/CNORM,
      .blue = 45.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Brown
      .name = "Brown",
      .red = 165.0/CNORM,
      .green = 42.0/CNORM,
      .blue = 42.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Maroon
      .name = "Maroon",
      .red = 128.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// White
      .name = "White",
      .red = 255.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 255.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Snow
      .name = "Snow",
      .red = 255.0/CNORM,
      .green = 250.0/CNORM,
      .blue = 250.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// HoneyDew
      .name = "HoneyDew",
      .red = 240.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 240.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MintCream
      .name = "MintCream",
      .red = 245.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 250.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Azure
      .name = "Azure",
      .red = 240.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 255.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// AliceBlue
      .name = "AliceBlue",
      .red = 240.0/CNORM,
      .green = 248.0/CNORM,
      .blue = 255.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// GhostWhite
      .name = "GhostWhite",
      .red = 248.0/CNORM,
      .green = 248.0/CNORM,
      .blue = 255.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// WhiteSmoke
      .name = "WhiteSmoke",
      .red = 245.0/CNORM,
      .green = 245.0/CNORM,
      .blue = 245.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// SeaShell
      .name = "SeaShell",
      .red = 255.0/CNORM,
      .green = 245.0/CNORM,
      .blue = 238.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Beige
      .name = "Beige",
      .red = 245.0/CNORM,
      .green = 245.0/CNORM,
      .blue = 220.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// OldLace
      .name = "OldLace",
      .red = 253.0/CNORM,
      .green = 245.0/CNORM,
      .blue = 230.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// FloralWhite
      .name = "FloralWhite",
      .red = 255.0/CNORM,
      .green = 250.0/CNORM,
      .blue = 240.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Ivory
      .name = "Ivory",
      .red = 255.0/CNORM,
      .green = 255.0/CNORM,
      .blue = 240.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// AntiqueWhite
      .name = "AntiqueWhite",
      .red = 250.0/CNORM,
      .green = 235.0/CNORM,
      .blue = 215.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Linen
      .name = "Linen",
      .red = 250.0/CNORM,
      .green = 240.0/CNORM,
      .blue = 230.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LavenderBlush
      .name = "LavenderBlush",
      .red = 255.0/CNORM,
      .green = 240.0/CNORM,
      .blue = 245.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// MistyRose
      .name = "MistyRose",
      .red = 255.0/CNORM,
      .green = 228.0/CNORM,
      .blue = 225.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Gainsboro
      .name = "Gainsboro",
      .red = 220.0/CNORM,
      .green = 220.0/CNORM,
      .blue = 220.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightGray
      .name = "LightGray",
      .red = 211.0/CNORM,
      .green = 211.0/CNORM,
      .blue = 211.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Silver
      .name = "Silver",
      .red = 192.0/CNORM,
      .green = 192.0/CNORM,
      .blue = 192.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkGray
      .name = "DarkGray",
      .red = 169.0/CNORM,
      .green = 169.0/CNORM,
      .blue = 169.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Gray
      .name = "Gray",
      .red = 128.0/CNORM,
      .green = 128.0/CNORM,
      .blue = 128.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DimGray
      .name = "DimGray",
      .red = 105.0/CNORM,
      .green = 105.0/CNORM,
      .blue = 105.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// LightSlateGray
      .name = "LightSlateGray",
      .red = 119.0/CNORM,
      .green = 136.0/CNORM,
      .blue = 153.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// SlateGray
      .name = "SlateGray",
      .red = 112.0/CNORM,
      .green = 128.0/CNORM,
      .blue = 144.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// DarkSlateGray
      .name = "DarkSlateGray",
      .red = 47.0/CNORM,
      .green = 79.0/CNORM,
      .blue = 79.0/CNORM,
      .alpha = 255.0/CNORM
   },
   {// Black
      .name = "Black",
      .red = 0.0/CNORM,
      .green = 0.0/CNORM,
      .blue = 0.0/CNORM,
      .alpha = 255.0/CNORM
   }
};

#undef NCOLORS

#undef CNORM
