noinst_LTLIBRARIES = libtinyexpr.la \
		     libslope.la

libtinyexpr_la_SOURCES = tinyexpr/tinyexpr.c
libtinyexpr_la_CFLAGS = 
libtinyexpr_la_LDFLAGS =

libslope_la_SOURCES = slope/slope/source/slope/chart.c \
		      slope/slope/source/slope/figure.c \
		      slope/slope/source/slope/legend.c \
		      slope/slope/source/slope/scale.c \
		      slope/slope/source/slope/xyaxis.c \
		      slope/slope/source/slope/xyseries.c \
		      slope/slope/source/slope/drawing.c \
		      slope/slope/source/slope/item.c \
		      slope/slope/source/slope/sampler.c \
		      slope/slope/source/slope/view.c \
		      slope/slope/source/slope/xyscale.c
libslope_la_CFLAGS = -I${srcdir}/slope/slope/source/ \
		     -I${srcdir}/slope/slope/include/ \
		     @GTK_CFLAGS@
libslope_la_LDFLAGS = @GTK_LIBS@ -rdynamic -lm

